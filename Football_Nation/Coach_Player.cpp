#include "coach_player.h"

CoachPlayer::CoachPlayer(const string& name, int age, const string& nationality, const Coach& c, const Player& p) :
	Person(name, age, nationality), Coach(c), Player(p)
{

}

ostream& operator<<(ostream& os, const CoachPlayer& cp)
{
	//os << cp << endl;
	return os;
}

