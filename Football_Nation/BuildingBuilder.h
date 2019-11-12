#ifndef __BUILDING_BUILDER_H
#define __BUILDING_BUILDER_H

#include "Builder.h"

class BuildingBuilder
{
public:
	void construct(Builder* builder, const string& name, char style, int height, int initialSize)
	{
		builder->buildRoof(style);
		builder->buildBody(height, initialSize);
		builder->buildBase(name);
	}
}; // Builder

#endif // !__BUILDING_BUILDER_H
