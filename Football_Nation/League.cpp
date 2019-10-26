#include "league.h"


League::League(const string& name, int numberOfTeams, Team** teams, int numberofreferees, Referee** referees) : name(name), numberOfTeams(numberOfTeams), teams(teams), numberOfReferees(numberofreferees),
referees(referees), fixtures(nullptr)
{
	this->playedFixtures = 0;
	refIndex = 0;
	referees = new Referee*[numberOfReferees];
	numberOfFixtures = (numberOfTeams - 1) * 2;
	rotationTeams = new Team*[numberOfTeams]; // makes a copy for rotations
	if (this->teams != nullptr)
	{
		teamIndex = numberOfTeams;
		for (int i = 0; i < numberOfTeams; i++)
			rotationTeams[i] = this->teams[i];
	}
	else
	{
		this->teams = new Team*[numberOfTeams];
		teamIndex = 0;
	}
}

League::~League()
{
	//delete[] name;
	delete[] referees;
	delete[] teams;
	delete[] rotationTeams;
	if (fixtures != nullptr)
	{
		for (int i = 0; i < numberOfFixtures; i++)
		{
			//delete[] fixtures[i]->getMatchesInFixture();
		}
		delete[] fixtures;
	}
}

int League::getNumberOfTeams() const
{
	return numberOfTeams;
}

Team** League::getTeams() const
{
	return teams;
}

void League::startSeason() throw (LeagueException)
{
	Fixture** createdFixtures = new Fixture*[numberOfFixtures];

	if (refIndex == 0) 
	{
		throw LeagueException("Must have at least one referee to start the season");
	}
	if (numberOfTeams % 2 == 1) 
	{
		throw LeagueException("Must have an even number of teams");
	}

	for (int i = 0; i < numberOfFixtures; i++)    // i = overall fixtures to create
	{
		LinkedList<Match>* matchesInFixture = new LinkedList<Match>();

		for (int matchNum = 0; matchNum < numberOfTeams/2; matchNum++)
		{
			Team* team1 = this->rotationTeams[matchNum];
			Team* team2 = this->rotationTeams[numberOfTeams - 1 - matchNum];

			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> random(MIN_RANDOM, numberOfReferees-1);

			Referee* ref = this->referees[random(rng)];
			Match* match;

			i < numberOfFixtures / 2 ? match = new Match(team1, team2, ref) : match = new Match(team2, team1, ref);   //set home/away teams based on fixture number

			matchesInFixture->insertToEnd(*match);
		}
		rotate();
		createdFixtures[i] = new Fixture(numberOfTeams / 2, i+1, matchesInFixture);
	}
	this->fixtures = createdFixtures;
}

void League::rotate()//rotates the teams clockwise, team 0 remains
{
	Team* tempTeam = rotationTeams[0];
	rotationTeams[0] = rotationTeams[numberOfTeams - 1];
	rotationTeams[numberOfTeams - 1] = tempTeam;

	//need to switch 0 and last team position

	Team* last = rotationTeams[numberOfTeams - 1];

	for (int i = numberOfTeams -1; i > 0 ; i--)
	{
		rotationTeams[i] = rotationTeams[i-1];
	}
	rotationTeams[0] = last;
}

const Fixture& League::playFixture() throw (LeagueException)
{
	/*if (isEnded())
		return nullptr;
		TODO : handle in main? */

	Fixture* fixtureToPlay = fixtures[playedFixtures++]; 
	cout <<  "==========================================================\n";

	for (int i = 0; i < fixtureToPlay->getGamesInFixture(); i++)
	{
		try
		{
			Match* match = &fixtureToPlay->getMatchesInFixture().get(i);
			match->playMatch();
		}
		catch (PlayMatchException & e)
		{
			throw LeagueException(e.getReason());
		}
	}
	fixtureToPlay->setHasPlayed(true);
	sortTeams();
	return *fixtureToPlay;
}



void League::setNumberOfReferees(int num)
{
	this->numberOfReferees = num;
	delete[] referees;
	referees = new Referee*[num];
	refIndex = 0;
}

void League::addReferee(Referee* referee) throw(NoSpaceException, NullPointerException)
{
	if (referee == nullptr)
		throw NullPointerException("referee");
	if (refIndex < numberOfReferees)
	{
		this->referees[refIndex] = referee;
		refIndex++;
	}
	else
		throw NoSpaceException("Referees at league", refIndex);
}

void League::addTeam(Team* team) throw(NoSpaceException, NullPointerException)
{
	if (team == nullptr)
		throw NullPointerException("team");
	if (teamIndex >= numberOfTeams)
		throw NoSpaceException("Teams in league", teamIndex);
	teams[teamIndex] = team;
	rotationTeams[teamIndex] = team;
	teamIndex++;
}

void League::showMostActiveReferee() const
{
	Referee* activeRef = referees[0];
	for (int i = 1; i < numberOfReferees; i++)
	{
		activeRef->getGamesPlayed() > referees[i]->getGamesPlayed()  ? 0 : activeRef = referees[i];
	}
	cout << "Most Active Referee: " << *activeRef << endl;
}

void League::showLeadingTeam() const
{
	Team* leadingTeam = teams[0]; // leading team will be at first index once the team array is sorted by points
	cout << "Leading Team: " << leadingTeam->getName() << " with " << leadingTeam->getPoints() << " Points" << endl;
}

void League::showLosingTeam() const
{
	Team* losingTeam = teams[numberOfTeams-1]; // last team is on the last index once the team array is sorted by points
	cout << "Team on last place: " << losingTeam->getName() << " with " << losingTeam->getPoints() << " Points" << endl;
}

void League::showLeadingScorer() const
{
	Player* goalLeader = this->teams[0]->getGoalLeader();
	for (int i = 1; i < this->numberOfTeams; i++)
	{
		if (*(teams[i]->getGoalLeader()) >= *goalLeader)
			goalLeader = teams[i]->getGoalLeader();
	}
	cout << "Player with most goals in league: " << goalLeader->getName() << " from " << goalLeader->getTeam()->getName() << " with " << goalLeader->getGoalScored() << " Goals!" << endl;
}

void League::sortTeams()
{
	int i, j;
	for (i = 0; i < numberOfTeams - 1; i++)
	{
		for (j = 0; j < numberOfTeams - i - 1; j++)
		{
			if (*teams[j+1] >= *teams[j]) //NOTE: checking is opposite because the table points is top down.
			{
				Team* temp = teams[j];
				teams[j] = teams[j + 1];
				teams[j + 1] = temp;
			}
		}
	}
}


ostream& operator<<(ostream& os, const League& league)
{
	os << "=======================================================\n" << "League Name: " << league.name
		<< ", Teams: " << league.numberOfTeams << ", Fixtures: " << league.numberOfFixtures << ".\n=======================================================\n";
	for (int i = 0; i < league.numberOfTeams; i++)
	{
		os << league.teams[i]->getName() << ": " << league.teams[i]->getPoints() << " Points";
		if (i == 0)
			os << "\t<< Winner! >>";
		os << endl;
	}
	return os;
}

bool League::isEnded()
{
	return numberOfFixtures == playedFixtures;
}

int League::getPlayedFixtures() const
{
	return playedFixtures;
}

void League::addPlayedFixture()
{
	this->playedFixtures += 1;
}
/*
void League::setName(const string& name)
{
	this->name = name;
}
*/
