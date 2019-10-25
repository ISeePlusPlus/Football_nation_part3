#ifndef __COACHPLAYER_H
#define __COACHPLAYER_H
#include "coach.h"
#include "player.h"

class CoachPlayer : public Coach, public Player
{
public:
	CoachPlayer(const string& name, int age, const string& nationality, const Coach& c, const Player& p);

	friend ostream& operator<<(ostream& os, const CoachPlayer& cp);
};
#endif //__COACHPLAYER_H