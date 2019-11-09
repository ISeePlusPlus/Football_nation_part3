#ifndef __WORLDCUP_H
#define __WORLDCUP_H

#include "team.h"
#include <iostream>
using namespace std;

class WorldCup
{
public:
	static WorldCup* getInstance();
	static void show();

private:
	WorldCup();
	WorldCup(const WorldCup& other);
	static WorldCup theCup;
};


#endif // !__WORLDCUP_H