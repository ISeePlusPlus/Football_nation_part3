#ifndef __TEAM_H
#define __TEAM_H

#include <iostream>
#include "referee.h"
#include <random>
#include "NoSpaceException.h"
#include "NullPointerException.h"
#include "coach.h"
#include "WorldCup.h"
#include "Building.h"

#pragma warning(disable:4290)
using namespace std;

const int MIN_RANDOM = 0;
const int MAX_RANDOM_ATTACK = 40;

class Coach;
class Player;
class Manager;
class WorldCup;

const int LINEUP_SIZE = 5; // size of the team lineup 
const int BENCH_SIZE = 10; // size of the bench. MUST BE > 0;
const int COACH_SIZE = 4; // size of the coach array.  MUST BE > 0;

class Team 
{
	friend WorldCup;
public:

	Team(const string& name,
		Manager * manager = nullptr);
	
	Team(const string& name,
		Manager* manager,
		int points);

	~Team();

	void setManager(Manager * manger); 
	void addPoints(int points); // a negative number can be delievered here, it will decrease the team's points.
	void addCoach(Coach &coach) throw (NoSpaceException);
	void addPlayer(Player &player) throw (NoSpaceException);
	void removePlayer(Player& Player);
	void removeCoach(Coach &coach);
	void addToLineup(Player &player) throw (NoSpaceException); //this will add player from the bench to the lineup. (will remove the other player from the bench).
	void fillLineup(); // only use this method on a team with empty lineup and bench with more than 5 players.
	void removeFromLineup(Player &player) throw (NoSpaceException); //this will remove the player from the lineup to the bench. NOTE: this function will not return a feedback if the index is already a nullptr
	vector<Player> getLineup() const; //returns the array of lineup
	vector<Player> getBench() const;
	Team operator+(int points) const; // add points to the team
	bool operator>=(const Team& otherTeam) const; //Team is bigger if team have more point
	bool operator<(const Team& otherTeam) const;
	bool operator==(const Team& otherTeam) const;
	const Team& operator=(const Team& other);
	friend ostream& operator<<(ostream& os, const Team& team);
	const string& getName() const;
//	int getLineupSize() const;
	void scoreGoal();
	Manager* getManager() const;
	int getPoints() const;
	Player* getGoalLeader();
	void setName(const string& name);
	vector<Coach> getCoaches() const;
	WorldCup* getCup() const;

	const vector<Player>& getLineupRef() const;
	const vector<Player>& getBenchRef() const;
	Building* getStadium();
	void setStadium(Building* stadium);
	Building* getFanClub();
	void setFanClub(Building* fc);


private:
	//void alignLineup(int strating_index); //Function to align the lineup array to the left, after removing a player.
	//void alignBench(int starting_index);
	string name;
	Manager* manager;
	vector<Player> benchPlayers;
	vector<Player> lineup;
	vector<Coach> coaches;
	int points;

	int currentBenchSize;
	int coachesSize;
	int currentLineup;

	WorldCup* cup;
	Building* homeStadium;
	Building* fanClub;
};

#endif // !__TEAM_H
