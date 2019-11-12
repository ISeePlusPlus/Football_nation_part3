#ifndef __FLOOR_H
#define __FLOOR_H

#include <iostream>
using namespace std;

class Floor
{
private:
	string name;
	int size;
	char texture;
public:
	Floor(const string& name, int capacity, char texture) : name(name), size(capacity), texture(texture) {}
	int getSize() const { return size; };
	string getName() const { return name; };
	char getTexture() const { return texture; };
};

#endif // !__FLOOR_H
