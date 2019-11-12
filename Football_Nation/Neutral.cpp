#include "Neutral.h"

Neutral::Neutral() {}

Neutral::Neutral(const Neutral* other) 
{

}

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
