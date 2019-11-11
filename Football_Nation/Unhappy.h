#ifndef __UNHAPPY_H
#define __UNHAPPY_H

#include "Mood.h"
#include "Happy.h"
#include "Neutral.h"

class Person;


class Unhappy : public Mood
{
public:
	Unhappy() { }
	virtual void neutral(Person& p) const;
	virtual void happy(Person& p) const;
};

#endif // !__UNHAPPY_H
