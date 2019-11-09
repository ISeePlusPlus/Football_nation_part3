#ifndef __WORLDCUP_H
#define __WORLDCUP_H

#include "team.h"
#include <iostream>
using namespace std;

class Team;

class WorldCup
{
public:
	static WorldCup* getInstance();
	static void assign(Team* team);
	friend ostream& operator<<(ostream& os, const WorldCup& cup);

private:
	WorldCup();
	WorldCup(const WorldCup& other);
	static Team* currentTeam;
	static WorldCup theCup;
};


#endif // !__WORLDCUP_H