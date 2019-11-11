#ifndef __NEUTRAL_H
#define __NEUTRAL_H

#include "Mood.h"
#include "Happy.h"
#include "Unhappy.h"

class Neutral : public Mood
{
public:
	Neutral() { }
	virtual void happy(Person& p) const;
	virtual void unhappy(Person& p) const;
};

#endif // !__NEUTRAL_H
