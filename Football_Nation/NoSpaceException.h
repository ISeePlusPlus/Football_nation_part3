#ifndef __NO_SPACE_EXCEPTION_H
#define __NO_SPACE_EXCEPTION_H

#pragma warning(disable:4996)

#include <iostream>
using namespace std;

class NoSpaceException
{
protected:
	int index;
	string structName;
public:
	NoSpaceException(const string& name, int index);
	virtual void show() const;
};

#endif // !__NO_SPACE_EXCEPTION_H