#ifndef __BUILDER_H
#define __BUILDER_H

#include "Building.h"
#include "Floor.h"

class Builder
{
public:
	Builder() { theStructure = new Building; }
	virtual ~Builder() { delete theStructure; }

	virtual void buildBase(string name) = 0;
	virtual void buildBody(int floors, int initialSize) = 0;
	virtual void buildRoof(char style) = 0;
	Building* getResult() const { return theStructure; }

protected:
	Building* theStructure;
}; // Builder

#endif // !__BUILDER_H
