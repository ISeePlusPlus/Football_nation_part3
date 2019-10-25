#ifndef __PERSON_EXCEPTION_H
#define __PERSON_EXCEPTION_H

#pragma warning(disable:4996)

#include <iostream>
#include "person.h"

using namespace std;

class PersonException
{
public:
	virtual const void show() const = 0;
};




#endif // !__PERSON_EXCEPTION_H