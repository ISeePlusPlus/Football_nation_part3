#include "Happy.h"

void Happy::neutral(Person& p) const
{
	p.setMood(new Neutral());
	delete this;
}

void Happy::unhappy(Person& p) const
{
	p.setMood(new Unhappy());
	delete this;
}