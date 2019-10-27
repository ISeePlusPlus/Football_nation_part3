#include "team.h"
#include "coach.h"
#include "player.h"
#include "manager.h"

Team::Team(const string& name, Manager* manager)
{
	setName(name);
	this->setManager(manager);
	this->coaches.reserve(COACH_SIZE);
	this->lineup.reserve(LINEUP_SIZE);
	this->benchPlayers.reserve(BENCH_SIZE);
	currentLineup = 0;
	this->points = 0;
}

Team::Team(const string& name, Manager* manager, vector<Coach> coaches, vector <Player> lineup, vector <Player> benchPlayers, int points)
{
	setName(name);
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

	coaches.clear();
	lineup.clear();
	benchPlayers.clear();
}

void Team::addPlayer(Player* player) throw (NoSpaceException)
{
	if (player != nullptr && player->getTeam() == nullptr) // adds a new player only if it is not null & he is not on any other team.
	{
		if (benchPlayers.size() < benchPlayers.capacity())
		{
			benchPlayers.push_back(*player);
		}
		else
			throw (NoSpaceException("Bench", currentBenchSize)); // bench is full
		benchPlayers.at(benchPlayers.size()-1).setTeam(this);
	}
}


void Team::addToLineup(Player* player) throw (NoSpaceException, NullPointerException)
{
	if (player == nullptr)
		throw NullPointerException("player");

	vector<Player>::iterator itrStart = lineup.begin();
	vector<Player>::iterator itrEnd = lineup.end();
	for ( ; itrStart != itrEnd; ++itrStart)  //return if the selected player is already in lineup
	{
		if (*itrStart == *player)
		{
			cout << "The player " << player->getName() << " is already in the team's lineup!";
			return;
		}
	}


	if (lineup.size() >= LINEUP_SIZE) //return if the lineup is full
		throw (NoSpaceException("Lineup", lineup.size()));

	
	vector<Player>::iterator itrStartBench = benchPlayers.begin();
	vector<Player>::iterator itrEndBench = benchPlayers.end();

	for (; itrStartBench != itrEndBench; ++itrStartBench)  //return if the selected player is already in lineup
	{
		if (*itrStartBench == *player)
		{
			benchPlayers.erase(itrStartBench);
			break;
		}
	}

	lineup.push_back(*player);
}

void Team::removePlayer(Player* player) throw (NullPointerException)
{


	if (player == nullptr)
		throw NullPointerException("player");

	vector<Player>::iterator itrStart = lineup.begin();
	vector<Player>::iterator itrEnd = lineup.end();
	for (; itrStart != itrEnd; ++itrStart)
	{
		if (&*itrStart == &*player)
		{
			lineup.erase(itrStart);
		}
	}

	vector<Player>::iterator itrStartBench = benchPlayers.begin();
	vector<Player>::iterator itrEndBench = benchPlayers.end();

	for (; itrStartBench != itrEndBench; ++itrStartBench)
	{
		if (*itrStartBench == *player)
		{
			benchPlayers.erase(itrStartBench);
		}
		}
		player->setTeam(nullptr);
	}


void Team::removeFromLineup(Player* player) throw (NoSpaceException, NullPointerException)
{

	if (player == nullptr)
		throw NullPointerException("player");
	if (benchPlayers.size() >= BENCH_SIZE) // only remove when there is a room in bench
		throw (NoSpaceException("Bench", currentBenchSize));

	vector<Player>::iterator itrStart = lineup.begin();
	vector<Player>::iterator itrEnd = lineup.end();

	for (; itrStart != itrEnd; ++itrStart)
	{
		if (*itrStart == *player)
		{
			lineup.erase(itrStart);
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

	vector<Coach>::iterator itrStart = coaches.begin();
	vector<Coach>::iterator itrEnd = coaches.end();

	for (; itrStart != itrEnd; ++itrStart)  //coach already in team
	{
		if (*itrStart == *coach)
			return;
	}

	if (coach == nullptr) // don't add nullptr coach
		throw NullPointerException("coach");

	coach->setTeam(nullptr);

	if (coaches.size() < coaches.capacity())
	{
		coaches.push_back(*coach);
	}
	else
		throw (NoSpaceException("Coach Position", coachesSize));
	coaches.at(coaches.size()-1).setTeam(this);
}

void Team::removeCoach(Coach* coach) throw (NullPointerException)
{

	if (coach == nullptr)
		throw NullPointerException("coach");

	vector<Coach>::iterator itrStart = coaches.begin();
	vector<Coach>::iterator itrEnd = coaches.end();

	for (; itrStart != itrEnd; ++itrStart)  
	{
		if (*itrStart == *coach)
			coaches.erase(itrStart);
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


bool Team::operator<(const Team & otherTeam) const
{
	return points < otherTeam.points;
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

	vector<Coach>::iterator itrStartCoach = team.getCoaches().begin();
	vector<Coach>::iterator itrEndCoach = team.getCoaches().end();

	for (; itrStartCoach != itrEndCoach; ++itrStartCoach)  //coach already in team
	{
		os << *itrStartCoach;
	}


	vector<Player>::iterator itrStart = team.getLineup().begin();
	vector<Player>::iterator itrEnd = team.getLineup().end();

	for (; itrStart != itrEnd; ++itrStart)  //coach already in team
	{
		os << *itrStart;
	}

	os << "--on bench--" << endl;


	itrStart = team.getBench().begin();
	itrEnd = team.getBench().end();

	for (; itrStart != itrEnd; ++itrStart)  //coach already in team
	{
		os << *itrStart;
	}

	return os;
}

const string& Team::getName() const
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

	/*
	vector<Player>::iterator itrStart = this->getLineup().begin();

	for (int i = 0; i < random(rng); i++)
	{
		++itrStart;
	}
	++(*itrStart);*/
}

int Team::getPoints() const
{
	return points;
}

Player* Team::getGoalLeader() const
{
	vector<Player>::iterator itrStart = this->getLineup().begin();
	vector<Player>::iterator itrEnd = this->getLineup().end();

	Player* goalLeader = &*itrStart;
	++itrStart;
	if (itrStart != itrEnd) 
	{
		for (; itrStart != itrEnd; ++itrStart)  
		{
			*itrStart >= *goalLeader ? goalLeader = &(*itrStart) : 0;
		}
	}

	itrStart = this->getBench().begin();
	itrEnd = this->getBench().begin();

	for (; itrStart != itrEnd; ++itrStart)  
	{
		*itrStart >= *goalLeader ? goalLeader = &(*itrStart) : 0;
	}

	return goalLeader;
}

void Team::setName(const string& name)
{
	this->name = name;
}

vector<Coach> Team::getCoaches() const
{
	return coaches;
}

vector<Player> Team::getLineup() const
{
	return lineup;
}

vector<Player> Team::getBench() const
{
	return benchPlayers;
}