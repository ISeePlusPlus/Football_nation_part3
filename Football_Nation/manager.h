#ifndef __MANAGER_H
#define __MANAGER_H
#include "Person.h"
#include "team.h"

class Team;

class Manager : public Person
{
	friend Team;
private:
	int yearsOfExperience;
	Team * currentTeam;
	Manager(const Manager& other);
	void setTeam(Team* team); // changing the team is only available from Team.

public:
	Manager(const string& name, int age, const string& nationality,int yearsOfExperience);
	friend ostream& operator<<(ostream& os, const Manager& manager);
	//~Manager();
};
#endif //__MANAGER_H
