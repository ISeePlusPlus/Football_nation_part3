#ifndef __PLAY_MATCH_EXCEPTION_H
#define __PLAY_MATCH_EXCEPTION_H

#include "team.h"
#include <iostream>
using namespace std;

class PlayMatchException
{
protected:
	Team* team;
	string reason;
public:
	PlayMatchException(Team* team, const string& reason);
	virtual void show() const;
	const string& getReason() const;
	Team* getTeam() const;
};

#endif // !__PLAY_MATCH_EXCEPTION_H

