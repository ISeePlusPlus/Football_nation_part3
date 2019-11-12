#ifndef __FANCLUB_H
#define __FANCLUB_H

#include "Builder.h"
#include "Floor.h"

class FanClub : public Builder
{
public:
	virtual void buildBase(string name) { theStructure->add(Floor("<3 " + name +" <3", 10, '=')); }
	virtual void buildBody(int floors, int initialSize)
	{
		for (int i = 0; i < floors; i++)
		{
			theStructure->add(Floor("          ", 10, '='));
		}
	}
	virtual void buildRoof(char style) { theStructure->add(Floor("    ", 5, style)); }
};

#endif // !__FANCLUB_H