#ifndef __HAPPY_H
#define __HAPPY_H

#include "Mood.h"
#include "Neutral.h"
#include "Unhappy.h"

class Happy : public Mood
{
public:
	Happy() { }
	virtual void neutral(Person& p) const;
	virtual void unhappy(Person& p) const;
};

#endif // !__HAPPY_H
