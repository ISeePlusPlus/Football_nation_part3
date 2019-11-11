#ifndef __MOOD_H
#define __MOOD_H

#include "person.h"

class Person;

class Mood
{
public:
	virtual void happy(Person& p) const {};
	virtual void neutral(Person& p) const {};
	virtual void unhappy(Person& p) const {};
};

#endif //__MOOD_H