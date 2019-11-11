#include "Neutral.h"

void Neutral::happy(Person& p) const
{
	p.setMood(new Happy());
	delete this;
}

void Neutral::unhappy(Person& p) const
{
	p.setMood(new Unhappy());
	delete this;
}