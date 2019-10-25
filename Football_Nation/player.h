#ifndef __PLAYER_H
#define __PLAYER_H
#pragma warning(disable:4996)

#include "person.h"
#include "team.h"
#include "role.h"
class Team;

const int STRIKER_BONUS = 6;
const int DEFENDER_BONUS = 3;
const int MID_BONUS = 2;

class Player : virtual public Person
{
	friend Team;
public:
	
	void show() const; //TODO: IMPLEMENT THE FUNCTION
	//double getRate();

	Player(const string& name, int age,
		const string& nationality,
		int attack, int defence,
		int goalkeeping, int goalScored = 0, int value=0,
		Role role= (Role)0);

	friend ostream& operator<<(ostream& os, const Player& p);
	const Player& operator++();
	bool operator >=(const Player& player) const; //Player is bigger if he scored more goles

	int getTotalStats() const; //TODO: IMPLEMENT THE FUNCTION

	//getters
	int getAttack() const;
	int getDefence() const;
	int getGoalkeeping() const;
	int getGoalScored() const;
	int getValue() const;
	Role getRole() const;
	Team* getTeam() const;
	//setters
	void setAttack(int atk);
	void setDefence(int def);
	void setGoalkeeping(int goalkeeping);
	void setValue(int val);
	void setRole(Role role);

protected:
	int attack;
	int defence;
	int goalkeeping;
	int goalScored;
	int value;
	Role role;
	Team* currentTeam;
	void setTeam(Team* team); // changing the team is only available through Team
	Player(const Player& other);

};

#endif //__PLAYER_H