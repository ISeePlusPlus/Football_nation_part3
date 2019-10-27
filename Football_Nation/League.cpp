#include "league.h"


League::League(const string& name, int numberOfTeams, vector<Team> teams, vector<Referee> referees, int numberofreferees) : name(name), numberOfTeams(numberOfTeams), teams(teams), numberOfReferees(numberofreferees),
referees(referees), fixtures(nullptr)
{
	this->playedFixtures = 0;
	referees.reserve(numberofreferees);
	numberOfFixtures = (numberOfTeams - 1) * 2;
	rotationTeams = teams; // makes a copy for rotations
}

League::~League()
{
	/*delete[] name;
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
	*/
	teams.clear();
	rotationTeams.clear();
	referees.clear();

	//TODO: NOT SURE THIS IS FINE. ALSO DEAL WITH FIXTURES
}

int League::getNumberOfTeams() const
{
	return numberOfTeams;
}

vector<Team>  League::getTeams() const
{
	return teams;
}

void League::startSeason() throw (LeagueException)
{
	Fixture** createdFixtures = new Fixture * [numberOfFixtures];

	if (referees.size() == 0) 
	{
		throw LeagueException("Must have at least one referee to start the season");
	}
	if (numberOfTeams % 2 == 1) 
	{
		throw LeagueException("Must have an even number of teams");
	}

	for (int i = 0; i < numberOfFixtures; i++)    // i = overall fixtures to create
	{
		Match** matchesInFixture = new Match * [numberOfTeams / 2];

		for (int matchNum = 0; matchNum < numberOfTeams/2; matchNum++)
		{
			Team* team1 = &rotationTeams.at(matchNum);
			Team* team2 = &rotationTeams.at(numberOfTeams - 1 - matchNum);

			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> random(MIN_RANDOM, numberOfReferees-1);

			Referee* ref = &referees.at(random(rng));
			Match* match;

			i < numberOfFixtures / 2 ? match = new Match(team1, team2, ref) : match = new Match(team2, team1, ref);   //set home/away teams based on fixture number

			matchesInFixture[matchNum] = match;
		}
	//	rotate();
		createdFixtures[i] = new Fixture(numberOfTeams / 2, i + 1, matchesInFixture);
	}
	this->fixtures = createdFixtures;
}
/*
void League::rotate()//rotates the teams clockwise, team 0 remains
{
	Team* tempTeam = &rotationTeams.at(0);
	//rotationTeams.at(0) = rotationTeams.at(numberOfTeams - 1);     //THIS ONE IS TRICKY!
	//rotationTeams.at(numberOfTeams - 1) = tempTeam;                   //solve above, solve this

	//rotationTeams.erase(rotationTeams.begin);
	//rotationTeams.insert(rotationTeams.begin, )                 I need to delete the first position, but then the tempteam is trash......

	//need to switch 0 and last team position

	Team* last = &rotationTeams[numberOfTeams - 1];

	for (int i = numberOfTeams -1; i > 0 ; i--)
	{
		rotationTeams[i] = rotationTeams[i-1];
	}
	rotationTeams[0] = last;
}
*/
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
			fixtureToPlay->getMatchesInFixture().get(i).playMatch();
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
//	delete[] referees;
//	referees = new Referee*[num];
//	refIndex = 0;
}

void League::addReferee(Referee& referee) throw(NoSpaceException)
{
	/*if (&referee == nullptr)
		throw NullPointerException("referee"); */
	if (referees.size() < numberOfReferees)
	{
		this->referees.insert(referees.begin(), referee);
	}
	else
		throw NoSpaceException("Referees at league", referees.size());
}

void League::addTeam(Team& team) throw (NoSpaceException)
{
/*	if (team == nullptr)
		throw NullPointerException("team");
		*/

	if (teams.size() >= numberOfTeams)
		throw NoSpaceException("Teams in league", teams.size());

	teams.insert(teams.begin(), team);
	rotationTeams.insert(rotationTeams.begin(), team);
}

void League::showMostActiveReferee() const
{
	vector<Referee>::const_iterator itrStart = referees.begin();
	vector<Referee>::const_iterator itrEnd = referees.end();

	Referee activeRef = *itrStart ;

	for (; itrStart != itrEnd; ++itrStart)
	{
		activeRef.getGamesPlayed() > (*itrStart).getGamesPlayed()  ? 0 : activeRef = *itrStart;
	}
	cout << "Most Active Referee: " << activeRef << endl;
}

void League::showLeadingTeam() const
{
	const Team* leadingTeam = &teams.at(0); // leading team will be at first index once the team array is sorted by points
	cout << "Leading Team: " << leadingTeam->getName() << " with " << leadingTeam->getPoints() << " Points" << endl;
}

void League::showLosingTeam() const
{
	const Team* losingTeam = &teams.at(numberOfTeams - 1); // last team is on the last index once the team array is sorted by points
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
