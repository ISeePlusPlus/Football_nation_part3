#include "team.h"
#include "coach.h"
#include "player.h"
#include "manager.h"

Team::Team(const string& name, Manager* manager) : cup(nullptr)
{
	setName(name);
	this->setManager(manager);
	this->coaches.reserve(COACH_SIZE);
	this->lineup.reserve(LINEUP_SIZE);
	this->benchPlayers.reserve(BENCH_SIZE);
	currentLineup = 0;
	this->points = 0;
}

Team::Team(const string& name, Manager* manager, int points) : cup(nullptr)
{
	setName(name);
//	this->manager = manager;
//	this->coaches = coaches;
//	this->lineup = lineup;
//	this->benchPlayers = benchPlayers;
//	currentBenchSize = 0;
//	coachesSize = 0;
//	currentLineup = 0;
	this->points = points;
}

Team::~Team()
{
	coaches.clear();
	lineup.clear();
	benchPlayers.clear();
}

void Team::addPlayer(Player &player) throw (NoSpaceException)
{
	if (player.getTeam() == nullptr) // adds a new player only if it is not null & he is not on any other team.
	{
		if (benchPlayers.size() < benchPlayers.capacity())
		{
			benchPlayers.push_back(player);
		}
		else
			throw (NoSpaceException("Bench", currentBenchSize)); // bench is full
		benchPlayers.at(benchPlayers.size()-1).setTeam(this);
	}
}

void Team::fillLineup()
{
	if (benchPlayers.size() < LINEUP_SIZE || lineup.size() != 0)
		return;
	for (int i=0; i<LINEUP_SIZE ; i++)
	{
		addToLineup(this->benchPlayers.at(0));
	}
}

void Team::addToLineup(Player &player) throw (NoSpaceException)
{

	vector<Player>::iterator itrStart = lineup.begin();
	vector<Player>::iterator itrEnd = lineup.end();
	for ( ; itrStart != itrEnd; ++itrStart)  //return if the selected player is already in lineup
	{
		if (*itrStart == player)
		{
			cout << "The player " << player.getName() << " is already in the team's lineup!" << endl;
			return;
		}
	}


	if (lineup.size() >= LINEUP_SIZE) //return if the lineup is full
		throw (NoSpaceException("Lineup", (int)lineup.size()));

	
	vector<Player>::iterator itrStartBench = benchPlayers.begin();
	vector<Player>::iterator itrEndBench = benchPlayers.end();

	for (; itrStartBench != itrEndBench; ++itrStartBench)  //return if the selected player is already in lineup
	{
		if (*itrStartBench == player)
		{
			lineup.push_back(player);
			benchPlayers.erase(itrStartBench);
			break;
		}
	}
}

void Team::removePlayer(Player &player)
{
	vector<Player>::iterator itrStart = lineup.begin();
	vector<Player>::iterator itrEnd = lineup.end();
	for (; itrStart != itrEnd; ++itrStart)
	{
		if (*itrStart == player)
		{
			lineup.erase(itrStart);
			break;
		}
	}

	vector<Player>::iterator itrStartBench = benchPlayers.begin();
	vector<Player>::iterator itrEndBench = benchPlayers.end();

	for (; itrStartBench != itrEndBench; ++itrStartBench)
	{
		if (*itrStartBench == player)
		{
			benchPlayers.erase(itrStartBench);
			break;
		}
	}
	player.setTeam(nullptr);
}


void Team::removeFromLineup(Player &player) throw (NoSpaceException)
{
	if (benchPlayers.size() >= BENCH_SIZE) // only remove when there is a room in bench
		throw (NoSpaceException("Bench", currentBenchSize));

	vector<Player>::iterator itrStart = lineup.begin();
	vector<Player>::iterator itrEnd = lineup.end();

	for (; itrStart != itrEnd; ++itrStart)
	{
		if (*itrStart == player)
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

void Team::addCoach(Coach &coach) throw (NoSpaceException)
{
	
	vector<Coach>::iterator itrStart = coaches.begin();
	vector<Coach>::iterator itrEnd = coaches.end();

	for (; itrStart != itrEnd; ++itrStart)  //coach already in team
	{
		if (*itrStart == coach)
			return;
	}

	coach.setTeam(nullptr);

	if (coaches.size() < coaches.capacity())
	{
		coaches.push_back(coach);
	}
	else
		throw (NoSpaceException("Coach Position", coachesSize));
	coaches.at(coaches.size()-1).setTeam(this);
}

void Team::removeCoach(Coach &coach)
{

	vector<Coach>::iterator itrStart = coaches.begin();
	vector<Coach>::iterator itrEnd = coaches.end();

	for (; itrStart != itrEnd; ++itrStart)  
	{
		if (*itrStart == coach)
		{
			coaches.erase(itrStart);
			return;
		}

	}
}

void Team::addPoints(int points)
{
	this->points += points;
}

const Team& Team::operator=(const Team& other)
{
	benchPlayers = other.getBench();
	lineup = other.getLineup();
	coaches = other.getCoaches();
	name = other.getName();
	manager = other.getManager();
	points = other.getPoints();
	return *this;
}

bool Team::operator==(const Team& other) const
{
	if (this->name == other.getName() && this->points == other.getPoints())
		return true;
	return false;
}

Team Team::operator+(int points) const
{
	points += 1;
	return *this;
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
	os << "Team Name: " << team.name << "," << "\tPoints: " << team.points;
	if (team.cup != nullptr)
		os << "\nCups: " << *team.cup << endl;
	os	<< "\n|| Manager || ";
	if (team.manager != nullptr)
	{
		os << *team.manager;
	}
	else
	{
		os << "None ";
	}

	os << "--in lineup--" << endl;

	vector<Player>::const_iterator itrStart = team.getLineupRef().begin();
	vector<Player>::const_iterator itrEnd = team.getLineupRef().end();

	for (; itrStart != itrEnd; ++itrStart)  //coach already in team
	{
		os << *itrStart;
	}

	os << "--on bench--" << endl;


	itrStart = team.getBenchRef().begin();
	itrEnd = team.getBenchRef().end();

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
/*
int Team::getLineupSize() const
{
	return currentLineup;
}*/

void Team::scoreGoal()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> random(MIN_RANDOM, LINEUP_SIZE - 1);

	vector<Player>::iterator itrStart = this->lineup.begin();

	for (int i = 0; i < random(rng); i++)
	{
		++itrStart;
	}
	++(*itrStart);
//	(*itrStart).setMood(new Happy());
}

int Team::getPoints() const
{
	return points;
}

Player* Team::getGoalLeader()
{
	Player* player = &lineup.at(0);
	vector<Player>::iterator itrStart = this->lineup.begin();
	vector<Player>::iterator itrEnd = this->lineup.end();

	for (; itrStart != itrEnd; ++itrStart)
		if (*itrStart >= *player)
			player = &(*itrStart);

	vector<Player>::iterator itrStartBench = this->benchPlayers.begin();
	vector<Player>::iterator itrEndBench = this->benchPlayers.end();

	for (; itrStartBench != itrEndBench; ++itrStartBench)
		if (*itrStartBench >= *player)
			player = &(*itrStartBench);

	return player;
}

void Team::setName(const string& name)
{
	this->name = name;
}

Manager* Team::getManager() const
{
	return manager;
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


WorldCup* Team::getCup() const
{
	return cup;
}

const vector<Player>& Team::getLineupRef() const
{
	return lineup;
}

const vector<Player>& Team::getBenchRef() const
{
	return benchPlayers;
}

Stadium* Team::getStadium()
{
	return homeStadium;
}

void Team::setStadium(Stadium* stadium)
{
	this->homeStadium = stadium;
}

FanClub* Team::getFanClub()
{
	if (fanClub)
		return fanClub;
	return nullptr;
}

void Team::setFanClub(FanClub* fc)
{
	this->fanClub = fc;
}
