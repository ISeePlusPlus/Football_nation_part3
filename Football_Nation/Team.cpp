#include "team.h"
#include "coach.h"
#include "player.h"
#include "manager.h"
#include <time.h>

Team::Team(const char* name, Manager* manager)
{
	this->name = new char[sizeof(name) + 1];
	strcpy(this->name, name);
	this->setManager(manager);
	this->coaches = new Coach*[INITIAL_COACH_SIZE];
	coachesSize = INITIAL_COACH_SIZE;
	for (int i = 0; i < coachesSize; i++)
	{
		coaches[i] = nullptr;
	}
	this->lineup = new Player*[LINEUP_SIZE];
	for (int i = 0; i < LINEUP_SIZE; i++)
	{
		lineup[i] = nullptr;
	}
	this->benchPlayers = new Player*[INITIAL_BENCH_SIZE];
	benchSize = INITIAL_BENCH_SIZE;
	for (int i = 0; i < benchSize; i++)
	{
		benchPlayers[i] = nullptr;
	}
	currentLineup = 0;
	this->points = 0;
}

Team::Team(const char* name, Manager* manager, Coach** coaches, Player** lineup, Player** benchPlayers, int points)
{
	this->name = new char[sizeof(name) + 1];
	strcpy(this->name, name);
	this->manager = manager;
	this->coaches = coaches;
	this->lineup = lineup;
	this->benchPlayers = benchPlayers;
	benchSize = 0;
	coachesSize = 0;
	currentLineup = 0;
	this->points = points;
}

Team::~Team()
{
	delete[] name;
	delete[] coaches;
	delete[] lineup;
	delete[] benchPlayers;
}

void Team::addPlayer(Player* player)
{
	if (!fillBench(player))
	{
		Player** tempArray = new Player*[benchSize * 2];
		for (int i = 0; i < benchSize; i++)
		{
			tempArray[i] = benchPlayers[i];
		}
		tempArray[benchSize] = player;
		benchSize *= 2;
		delete[] benchPlayers;
		benchPlayers = tempArray;
	}
}


void Team::addToLineup(Player* player)
{
	if (player == nullptr)
		return;

	for (int i = 0; i < currentLineup; i++) //return if the selected player is already in lineup
	{
		if (lineup[i] == player)
			return;
	}

	if (currentLineup >= LINEUP_SIZE) //return if the lineup is full
		return;

	removePlayer(player);
	lineup[currentLineup] = player;
	currentLineup++;
}

void Team::removePlayer(Player* player)
{
	if (player == nullptr)
		return;

	for (int i = 0; i < currentLineup; i++)
	{
		if (lineup[i] == player)
		{
			lineup[i] = nullptr;
			alignLineup(i);
			currentLineup--;
		}
	}
	for (int i = 0; i < benchSize; i++)
	{
		if (benchPlayers[i] == player)
		{
			benchPlayers[i] = nullptr;
		}
	}
}


void Team::removeFromLineup(Player* player)
{
	if (player == nullptr)
		return;

	for (int i = 0; i < currentLineup; i++)
	{
		if (lineup[i] == player)
		{
			lineup[i] = nullptr;
			alignLineup(i);
			currentLineup--;
		}
	}
	addPlayer(player);
}


void Team::setManager(Manager* manager)
{
	this->manager = manager;
	if (manager != nullptr)
		manager->setTeam(this);
}

void Team::addCoach(Coach* coach)
{
	for (int i = 0; i < coachesSize ; i++)
	{
		if (coaches[i] == coach)
			return;
	}
	if (coach == nullptr)
		return;
	coach->setTeam(nullptr);
	if (!fillCoach(coach))
	{
		Coach** tempArray = new Coach*[coachesSize * 2];
		for (int i = 0; i < coachesSize; i++)
		{
			tempArray[i] = coaches[i];
		}
		tempArray[coachesSize] = coach;
		coachesSize *= 2;
		delete[] coaches;
		coaches = tempArray;
	}
	coach->setTeam(this);
}

void Team::removeCoach(Coach* coach)
{
	if (coach == nullptr)
		return;
	for (int i = 0; i < coachesSize; i++)
	{
		if (coaches[i] == coach)
		{
			coaches[i]->setTeam(nullptr);
			coaches[i] = nullptr;
			coachesSize--;
		}
	}
}

Team Team::operator+(int points) const
{
	return Team(name, manager, coaches, lineup, benchPlayers, this->points + points);
}

bool Team::operator>=(const Team& otherTeam) const
{
	return points >= otherTeam.points;
}


ostream& operator<<(ostream& os, const Team& team)
{
	os << "Team Name: " << team.name << "," << "\tPoints: " << team.points << "\n|| Manager || ";
	if (team.manager != nullptr)
	{
		os << *team.manager;
	}
	else
	{
		os << "None ";
	}
		os << "\n|| Coaches ||" << endl;
	for (int i = 0; i < team.coachesSize; i++)
	{
		if (team.coaches[i] != nullptr)
			os << *(team.coaches[i]);
	}
	os << "|| Players ||\n--Lineup--" << endl;
	for (int i = 0; i < team.currentLineup; i++)
	{
		os << *team.lineup[i];
	}
	os << "--on bench--" << endl;
	for (int i = 0; i < team.benchSize; i++)
	{
		if (team.benchPlayers[i] != nullptr)
			os << *team.benchPlayers[i];
	}
	return os;
}

char* Team::getName() const
{
	return name;
}

void Team::scoreGoal()
{
	cout << name << "Scored a goal!" << endl;
	srand(time(NULL));
	int random = rand() % LINEUP_SIZE;
	++(this->getLineup()[random]);    //add a goal to a player from team
	
}

int Team::getPoints()
{
	return points;
}

Player* Team::getGoalLeader() const
{
	Player* goalLeader = lineup[0];

	for (int i = 1; i < LINEUP_SIZE; i++)
		lineup[i] >= goalLeader ? goalLeader = lineup[i] : 0;

	for (int i = 0; i < benchSize; i++)
		benchPlayers[i] >= goalLeader ? goalLeader = benchPlayers[i] : 0;

	return goalLeader;
}

Player** Team::getLineup()
{
	return lineup;
}

//below functions are for use inside this class only! (they are private)
bool Team::fillBench(Player* player)
{
	for (int i = 0; i < benchSize; i++)
	{
		if (benchPlayers[i] == nullptr)
		{
			benchPlayers[i] = player;
			return true;
		}
	}
	return false;
}

bool Team::fillCoach(Coach* coach)
{
	for (int i = 0; i < coachesSize; i++)
	{
		if (coaches[i] == nullptr)
		{
			coaches[i] = coach;
			return true;
		}
	}
	return false;
}

void Team::alignLineup(int starting_index)
{
	for (int i = starting_index; i < LINEUP_SIZE; i++)
	{
		lineup[i] = lineup[i + 1];
	}
	lineup[LINEUP_SIZE] = nullptr;
}