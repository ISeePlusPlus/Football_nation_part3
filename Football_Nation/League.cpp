#include "league.h"


League::League(const string& name, int numberOfTeams) : name(name), numberOfTeams(numberOfTeams), numberOfReferees(0)
{
	this->playedFixtures = 0;
	referees.reserve(0);
	teams.reserve(numberOfTeams);
	numberOfFixtures = (numberOfTeams - 1) * 2;
	this->fixtures.reserve(numberOfFixtures);
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
	referees.clear();
	//TODO: NOT SURE THIS IS FINE. ALSO DEAL WITH FIXTURES
}

int League::getNumberOfTeams() const
{
	return numberOfTeams;
}

vector<Team>&  League::getTeams()
{
	return teams;
}

void League::startSeason() throw (LeagueException)
{
	rotationTeams = teams;
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
		vector<Match> matchesInFixture;

		for (int matchNum = 0; matchNum < numberOfTeams/2; matchNum++)
		{
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> random(MIN_RANDOM, numberOfReferees-1);

			Referee* ref = &referees.at(random(rng));
			Match* match;
			int idx = numberOfTeams - 1 - matchNum;
			Team& t1 = *(find(teams.begin(), teams.end(), rotationTeams.at(matchNum)));
			Team& t2 = *(find(teams.begin(), teams.end(), rotationTeams.at(idx)));
			i < numberOfFixtures / 2 ? 
				match = new Match(t1, t2, ref) :
				match = new Match(t2, t1, ref);   //set home/away teams based on fixture number

			matchesInFixture.push_back(*match);
		}
		fixtures.push_back(Fixture(numberOfTeams / 2, i + 1, matchesInFixture));
		rotate();
	}

}

void League::rotate()//rotates the teams clockwise, team 0 remains
{
	//std::swap(teams.at(0),teams.at(teams.size()-1));
	iter_swap(rotationTeams.begin(), rotationTeams.end()-1);
	std::rotate(rotationTeams.rbegin(), rotationTeams.rbegin() + 1, rotationTeams.rend());
}

const Fixture& League::playFixture() throw (LeagueException)
{
	/*if (isEnded())
		return nullptr;
		TODO : handle in main? */
	
	Fixture* fixtureToPlay = &fixtures.at(playedFixtures++); 
	cout <<  "================================================================\n";

	for (int i = 0; i < fixtureToPlay->getGamesInFixture(); i++)
	{
		try
		{
			fixtureToPlay->getMatchesInFixture().at(i).playMatch();
		}
		catch (PlayMatchException & e)
		{
			throw LeagueException(e.getReason());
		}
	}
	leaderBoard = teams;
	sortTeams();
	fixtureToPlay->setHasPlayed(true);
	return *fixtureToPlay;
}



void League::setNumberOfReferees(int num)
{
	this->numberOfReferees = num;
//	delete[] referees;
//	referees = new Referee*[num];
//	refIndex = 0;
}

void League::addReferee(Referee& referee) throw (NoSpaceException)
{
	/*if (&referee == nullptr)
		throw NullPointerException("referee"); */
	if (referees.size() < numberOfReferees)
	{
		this->referees.insert(referees.begin(), referee);
	}
	else
		throw NoSpaceException("Referees at league", (int)referees.size());
}

void League::addTeam(Team& team) throw (NoSpaceException)
{
/*	if (team == nullptr)
		throw NullPointerException("team");
		*/
	
	if (teams.size() >= numberOfTeams)
		throw NoSpaceException("Teams in league", (int)teams.size());

	teams.insert(teams.end(), team);
}

void League::showMostActiveReferee() const
{
	vector<Referee>::const_iterator itrStart = referees.begin();
	vector<Referee>::const_iterator itrEnd = referees.end();

	Referee activeRef = *itrStart ;

	for (; itrStart != itrEnd; ++itrStart)
	{
		if (activeRef.getGamesPlayed() < (*itrStart).getGamesPlayed())
			activeRef = *itrStart;
	}
	cout << "Most Active Referee: " << activeRef << endl;
}

void League::showLeadingTeam() const
{
	const Team* leadingTeam = &leaderBoard.at(0); // leading team will be at first index once the team array is sorted by points
	cout << "Leading Team: " << leadingTeam->getName() << " with " << leadingTeam->getPoints() << " Points" << endl;
}

void League::showLosingTeam() const
{
	int idx = numberOfTeams - 1;
	const Team* losingTeam = &leaderBoard.at(idx); // last team is on the last index once the team array is sorted by points
	cout << "Team on last place: " << losingTeam->getName() << " with " << losingTeam->getPoints() << " Points" << endl;
}

void League::showLeadingScorer()
{
	Player* leader = teams.at(0).getGoalLeader();

	vector<Team>::iterator itrStart = this->teams.begin();
	vector<Team>::iterator itrEnd = this->teams.end();

	for (; itrStart != itrEnd; ++itrStart)
	{
		Player* player = itrStart->getGoalLeader();
		if (*player >= *leader)
			leader = player;
	}
	cout << "Player with most goals in league: " << leader->getName() << " from " << leader->getTeam()->getName() << " with " << leader->getGoalScored() << " Goals!" << endl;
}

void League::sortTeams() // sorts the teams by points (in Team::operator<) and then reverse it so the team with highest points will be first in the table.
{
	sort(leaderBoard.begin(), leaderBoard.end());
	reverse(leaderBoard.begin(), leaderBoard.end());
}


ostream& operator<<(ostream& os, const League& league)
{
	os << "================================================================\n" << "League Name: " << league.name
		<< ", Teams: " << league.numberOfTeams << ", Fixtures: " << league.numberOfFixtures << ".\n================================================================\n";
	for (int i = 0; i < league.numberOfTeams; i++)
	{
		os << league.leaderBoard.at(i).getName() << ": " << league.leaderBoard.at(i).getPoints() << " Points";
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

Team& League::getWinner() // leaderBoard must be sorted to get the actual winner
{
	return *(find(teams.begin(), teams.end(), leaderBoard.at(0)));
}

vector<Fixture>& League::getFixtures()
{
	return fixtures;
}

/*
void League::setName(const string& name)
{
	this->name = name;
}
*/
