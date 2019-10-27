#ifndef __TEAM_H
#define __TEAM_H

#include <iostream>
#include "referee.h"
#include <random>
#include "NoSpaceException.h"
#include "NullPointerException.h"

#pragma warning(disable:4290)
using namespace std;

const int MIN_RANDOM = 0;
const int MAX_RANDOM_ATTACK = 40;

class Coach;
class Player;
class Manager;

const int LINEUP_SIZE = 5; // size of the team lineup 
const int BENCH_SIZE = 10; // size of the bench. MUST BE > 0;
const int COACH_SIZE = 4; // size of the coach array.  MUST BE > 0;

class Team 
{

public:

	Team(const string& name,
		Manager * manager = nullptr);

	Team(const string& name,
		Manager* manager,
		vector<Coach> coaches,
		vector<Player> lineup,
		vector<Player> benchPlayers,
		int points);

	~Team();

	void setManager(Manager * manger); 
	void addPoints(int points); // a negative number can be delievered here, it will decrease the team's points.
	void addCoach(Coach * coach) throw (NoSpaceException, NullPointerException);
	void addPlayer(Player * player) throw (NoSpaceException);
	void removePlayer(Player* Player) throw (NullPointerException);
	void removeCoach(Coach* coach) throw (NullPointerException);
	void addToLineup(Player* player) throw (NoSpaceException, NullPointerException); //this will add player from the bench to the lineup. (will remove the other player from the bench).
	void removeFromLineup(Player* player) throw (NoSpaceException, NullPointerException); //this will remove the player from the lineup to the bench. NOTE: this function will not return a feedback if the index is already a nullptr
	vector<Player> getLineup() const; //returns the array of lineup
	vector<Player> getBench() const;
	Team operator+(int points) const; // add points to the team
	bool operator>=(const Team& otherTeam) const; //Team is bigger if team have more point
	bool operator<(const Team & otherTeam) const;
	friend ostream& operator<<(ostream& os, const Team& team);
	const string& getName() const;
	int getLineupSize() const;
	void scoreGoal();
	int getPoints() const;
	Player* getGoalLeader() const;
	void setName(const string& name);
	vector<Coach> getCoaches() const;

private:
	//void alignLineup(int strating_index); //Function to align the lineup array to the left, after removing a player.
	//void alignBench(int starting_index);
	string name;
	Team(const Team& other);
	const Team& operator=(const Team& other) = delete;
	Manager* manager;
	vector<Coach> coaches;
	vector<Player> benchPlayers;
	vector<Player> lineup;
	int points;

	int currentBenchSize;
	int coachesSize;
	int currentLineup;
};

#endif // !__TEAM_H
