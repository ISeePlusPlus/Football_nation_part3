#ifndef __STADIUM_H
#define __STADIUM_H

#include "Builder.h"
#include "Floor.h"

class Stadium : public Builder
{
public:
	virtual void buildBase(string name) { theStructure->add(Floor("STADIUM of "+name, 18, '=')); }
	virtual void buildBody(int floors, int initialSize)
	{
		for (int i = 0; i < floors; i++)
		{
			theStructure->add(Floor("          ", initialSize - i, '-'));
		}
	}
	virtual void buildRoof(char style) { theStructure->add(Floor("     ", 14, style)); }
};

#endif // !__STADIUM_H