#include "WorldCup.h"

WorldCup WorldCup::theCup;
Team* WorldCup::currentTeam = nullptr;

WorldCup::WorldCup()
{
}

void WorldCup::assign(Team* team)
{
	if (currentTeam != nullptr)
	{
		currentTeam->cup = nullptr;
	}
	team->cup = getInstance();
	currentTeam = team;
}

ostream& operator<<(ostream& os, const WorldCup& cup)
{
	os << "<{| World Cup |}>";
	return os;
}

WorldCup* WorldCup::getInstance()
{
	return &theCup;
}

