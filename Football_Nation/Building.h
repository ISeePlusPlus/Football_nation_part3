#ifndef __BUILDING_H
#define __BUILDING_H

#include "Floor.h"
#include <vector>

class Building
{
private:
	vector<Floor> floors;
public:
	void add(const Floor& floor);
	void show() const;
};

#endif // !__BUILDING_H
