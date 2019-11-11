#ifndef __OBSERVER_H
#define __OBSERVER_H

#include "match.h"
#include <iostream>
using namespace std;

class Match;

class Observer
{
public:
	Observer() {}
	virtual void notify(Match* match, Team* winner) = 0;
}; // Observer

#endif // !__OBSERVER_H
