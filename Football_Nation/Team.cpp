#include "team.h"
#include "coach.h"
#include "player.h"
#include "manager.h"

Team::Team(const char* name, Manager* manager)
{
	this->name = new char[sizeof(name) + 1];
	strcpy(this->name, name);
	this->setManager(manager);
	this->coaches = new Coach*[COACH_SIZE];
	coachesSize = 0;
	for (int i = 0; i < coachesSize; i++)
	{
		coaches[i] = nullptr;
	}
	this->lineup = new Player*[LINEUP_SIZE];
	for (int i = 0; i < LINEUP_SIZE; i++)
	{
		lineup[i] = nullptr;
	}
	this->benchPlayers = new Player*[BENCH_SIZE];
	currentBenchSize = 0;
	
	for (int i = 0; i < BENCH_SIZE; i++)
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
	currentBenchSize = 0;
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

void Team::addPlayer(Player* player) throw (NoSpaceException)
{
	if (player != nullptr && player->getTeam() == nullptr) // adds a new player only if it is not null & he is not on any other team.
	{
		if (!fillBench(player))
		{
			/* ---> old code <---
			cout << "array of bench is full so we need to size it up\n\n\n";
			int arr_multiplier = benchSize * 2;
			Player** tempArray = new Player*[arr_multiplier];
			for (int i = 0; i < benchSize; i++)
			{
				tempArray[i] = benchPlayers[i];
			}
			delete[] benchPlayers;
			benchPlayers = tempArray;
			tempArray[benchSize] = player;
			benchSize *= 2;
			cout << "now bench is size: " << benchSize << endl;
			*/
			throw (NoSpaceException("Bench", currentBenchSize)); // bench is full
		}
		currentBenchSize++;
		player->setTeam(this);
	}
}


void Team::addToLineup(Player* player) throw (NoSpaceException, NullPointerException)
{
	if (player == nullptr)
		throw NullPointerException("player");
	for (int i = 0; i < currentLineup; i++) //return if the selected player is already in lineup
	{
		if (lineup[i] == player)
		{
			cout << "The player " << player->getName() << " is already in the team's lineup!";
			return;
		}
	}
	if (currentLineup >= LINEUP_SIZE) //return if the lineup is full
		throw (NoSpaceException("Lineup", currentLineup));

	for (int i = 0; i < currentBenchSize; i++)
	{
		if (benchPlayers[i] == player)
		{
			benchPlayers[i] = nullptr;
			alignBench(i);
			currentBenchSize--;
			i = currentBenchSize;
		}

	}
	lineup[currentLineup] = player;
	currentLineup++;
}

void Team::removePlayer(Player* player) throw (NullPointerException)
{
	if (player == nullptr)
		throw NullPointerException("player");

	for (int i = 0; i < currentLineup; i++)
	{
		if (lineup[i] == player)
		{
			lineup[i] = nullptr;
			alignLineup(i);
			currentLineup--;
		}
	}
	for (int i = 0; i < currentBenchSize; i++)
	{
		if (benchPlayers[i] == player)
		{
			benchPlayers[i] = nullptr;
			alignBench(i);
			currentBenchSize--;
		}
	}
	player->setTeam(nullptr);
}


void Team::removeFromLineup(Player* player) throw (NoSpaceException, NullPointerException)
{
	if (player == nullptr)
		throw NullPointerException("player");
	if (currentBenchSize >= BENCH_SIZE) // only remove when there is a room in bench
		throw (NoSpaceException("Bench", currentBenchSize));

	for (int i = 0; i < currentLineup; i++)
	{
		if (lineup[i] == player)
		{
			lineup[i] = nullptr;
			alignLineup(i);
			currentLineup--;
			addPlayer(player);
			return;
		}
	}
}


void Team::setManager(Manager* manager)
{
	this->manager = manager;
	if (manager != nullptr)
		manager->setTeam(this);
}

void Team::addCoach(Coach* coach) throw (NoSpaceException, NullPointerException)
{
	for (int i = 0; i < coachesSize ; i++) // return if the coach is already in team
	{
		if (coaches[i] == coach)
			return;
	}
	if (coach == nullptr) // don't add nullptr coach
		throw NullPointerException("coach");

	coach->setTeam(nullptr);
	if (!fillCoach(coach))
	{
		throw (NoSpaceException("Coach Position", coachesSize));
	}
	coach->setTeam(this);
}

void Team::removeCoach(Coach* coach) throw (NullPointerException)
{
	if (coach == nullptr)
		throw NullPointerException("coach");
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

void Team::addPoints(int points)
{
	this->points += points;
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
	for (int i = 0; i < team.currentBenchSize; i++)
	{
		os << *team.benchPlayers[i];
	}
	return os;
}

char* Team::getName() const
{
	return name;
}

int Team::getLineupSize() const
{
	return currentLineup;
}

void Team::scoreGoal()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> random(MIN_RANDOM, LINEUP_SIZE - 1);

	Player* scorer = this->getLineup()[random(rng)];    //add a goal to a player from team
	++(*scorer);
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

	for (int i = 0; i < currentBenchSize; i++)
		benchPlayers[i] >= goalLeader ? goalLeader = benchPlayers[i] : 0;

	return goalLeader;
}

Player** Team::getLineup() const
{
	return lineup;
}

Player** Team::getBench() const
{
	return benchPlayers;
}

//below functions are for use inside this class only! (they are private)
bool Team::fillBench(Player* player)
{
	if (currentBenchSize < BENCH_SIZE)
	{
		benchPlayers[currentBenchSize] = player;
		return true;
	}
	return false;
}

bool Team::fillCoach(Coach* coach)
{
	if (coachesSize < COACH_SIZE)
	{
		coaches[coachesSize] = coach;
		coachesSize++;
		return true;
	}
	return false;
}

void Team::alignLineup(int starting_index)
{
	for (int i = starting_index; i < LINEUP_SIZE-1; i++)
	{
		lineup[i] = lineup[i + 1];
	}
	lineup[LINEUP_SIZE] = nullptr;
}

void Team::alignBench(int starting_index)
{
	for (int i = starting_index; i < currentBenchSize - 1; i++)
	{
		benchPlayers[i] = benchPlayers[i + 1];
	}
	benchPlayers[currentBenchSize] = nullptr;
}