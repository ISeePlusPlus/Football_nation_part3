#include "Unhappy.h"

void Unhappy::neutral(Person& p) const
{
	p.setMood(new Neutral());
	delete this;
}

void Unhappy::happy(Person& p) const
{
	p.setMood(new Happy());
	delete this;
}