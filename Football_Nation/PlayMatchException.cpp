#include "PlayMatchException.h"

PlayMatchException::PlayMatchException(Team* team, const string& reason) : team(team)
{
	this->reason = reason;
}

void PlayMatchException::show() const
{
	cout << "Match cannot be played because Team " << team->getName() << " " << reason << endl;
}

Team* PlayMatchException::getTeam() const
{
	return team;
}

const string& PlayMatchException::getReason() const
{
	return reason;
}