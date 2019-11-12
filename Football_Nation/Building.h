#ifndef __BUILDING_H
#define __BUILDING_H

#include "Floor.h"
#include <vector>

class Building
{
public:
	void add(const Floor& floor);
	void show() const;
private:
	vector<Floor> floors;
};

#endif // !__BUILDING_H
