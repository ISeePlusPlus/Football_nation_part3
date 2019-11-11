#ifndef __GAMBLER_H
#define __GAMBLER_H

#include "Observer.h"
#include "person.h"
#include "team.h"
#include "match.h"
#include <map>

class Person;
class Observer;
class Team;
class Match;

const int REWARD = 100;

class Gambler : public Person, public Observer
{
private:
	int prizeMoney;
	map <Match* , Team*> bets;
public:
	Gambler(const string& name, int age, const string& nationality);
	virtual void notify(Match* match, Team* winner);
	int getPrizeMoney() const;
	void placeBet(Match& match, Team& winner);

};

#endif // !__GAMBLER_H
