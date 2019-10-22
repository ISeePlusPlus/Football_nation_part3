#include "league.h"
#include <time.h>

League::League(const char* name, int numberOfTeams, Team** teams, int numberofreferees, Referee** referees) : numberOfTeams(numberOfTeams), teams(teams), numberOfReferees(numberofreferees),
referees(referees), fixtures(nullptr)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	playedFixtures = 0;
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
	delete[] teams;
	delete[] rotationTeams;
	if (fixtures != nullptr)
	{
		for (int i = 0; i < numberOfFixtures; i++)
		{
			delete[] fixtures[i]->getMatchesInFixture();
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

void League::startSeason()
{
	Fixture** createdFixtures = new Fixture*[numberOfFixtures];

	for (int i = 0; i < numberOfFixtures; i++)    // i = overall fixtures to create
	{
		
		Match** matchesInFixture = new Match*[numberOfTeams / 2] ;

		for (int matchNum = 0; matchNum < numberOfTeams/2; matchNum++)
		{
			Team* team1 = this->rotationTeams[matchNum];
			Team* team2 = this->rotationTeams[numberOfTeams - 1 - matchNum];

			srand(time(NULL));
			int	random = numberOfReferees==1? 0 : (rand() % (numberOfReferees -1)) ;
			Referee* ref = this->referees[random];
			Match* match;

			i < numberOfFixtures / 2 ? match = new Match(team1, team2, ref) : match = new Match(team2, team1, ref);   //set home/away teams based on fixture number

			matchesInFixture[matchNum] = match;
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

const Fixture& League::playFixture()
{
	/*if (isEnded())
		return nullptr;
		TODO : handle in main? */

	Fixture* fixtureToPlay = fixtures[playedFixtures++]; 

	
	for (int i = 0; i < fixtureToPlay->getGamesInFixture(); i++)
	{
		fixtureToPlay->getMatchesInFixture()[i]->playMatch();
	}
	fixtureToPlay->setHasPlayed(true);
	sortTeams();
	return *fixtureToPlay;
}



void League::setNumberOfReferees(int num)
{
	Referee** temp = new Referee*[num];
	for (int i = 0; i < numberOfReferees; i++)
	{
		temp[i] = referees[i];
		if (i == num-1)
			break;
	}
	delete[] referees;
	referees = temp;
	numberOfReferees = num;
}

void League::addReferee(Referee* referee)
{
	for (int i = 0; i < numberOfReferees; i++)
	{
		if (referees[i] == nullptr)
		{
			referees[i] = referee;
			return;
		}
	}
}

void League::addTeam(Team* team)
{
	if (teamIndex >= numberOfTeams)
		return;
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
	cout << &activeRef << endl;
}

void League::showLeadingTeam() const
{
	Team* leadingTeam = teams[0];

	for (int i = 1; i < numberOfTeams; i++)
	{
		leadingTeam->getPoints() > teams[i]->getPoints() ? 0 : leadingTeam = teams[i];
	}
	cout << &leadingTeam << endl;
}

void League::showLosingTeam() const
{
	Team* losingTeam = teams[0];

	for (int i = 1; i < numberOfTeams; i++)
	{
		losingTeam->getPoints() > teams[i]->getPoints() ? losingTeam = teams[i] : 0;
	}
	cout << &losingTeam << endl;
}

void League::showLeadingScorer() const
{
	Player* goalLeader = this->teams[0]->getGoalLeader();

	for (int i = 0; i < numberOfTeams ; i++) 
	{
		this->teams[i]->getGoalLeader() >= goalLeader ? goalLeader = teams[i]->getGoalLeader() : 0 ;
	}
	cout << &goalLeader << endl;
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