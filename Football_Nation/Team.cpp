#include "team.h"
#include "coach.h"


Team::Team(const char* name, Manager* manager = nullptr, Coach* coaches = nullptr, Player* lineup = nullptr, Player* benchPlayers = nullptr, int points = 0)
{
	this->name = new char[sizeof(name) + 1];
	strcpy(this->name, name);
	this->manager = manager;
	this->coaches = new Coach*[INITIAL_COACH_SIZE];
	this->lineup = new Player*[LINEUP_SIZE];
	this->benchPlayers = new Player*[INITIAL_BENCH_SIZE];
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


void Team::addToLineup(int index)
{
	if (index > LINEUP_SIZE)
	{
		Player* pl = benchPlayers[index - LINEUP_SIZE];
		removePlayer(index);
		lineup[currentLineup] = pl;
		currentLineup++;
	}
	// if the code comes here it supposed to throw an exception.
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

bool Team::fillBench(Player* player)
{
	for (int i = 0; i < benchSize; i++)
	{
		if (benchPlayers[i] = nullptr)
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
		if (coaches[i] = nullptr)
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