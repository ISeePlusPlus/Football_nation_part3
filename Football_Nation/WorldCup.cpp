#include "WorldCup.h"

WorldCup WorldCup::theCup;

WorldCup::WorldCup()
{

}

void WorldCup::show()
{
	cout << "this is the cup\n";
}

WorldCup* WorldCup::getInstance()
{
	return &theCup;
}

