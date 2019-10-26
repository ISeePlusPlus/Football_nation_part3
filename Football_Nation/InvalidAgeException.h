#ifndef __INVALID_AGE_EXCEPTION
#define __INVALID_AGE_EXCEPTION

#include "person.h"

class InvalidAgeException
{
private:
	int age;
public:
	InvalidAgeException(int age)
	{
		this->age = age;
	}
	const void show() const
	{
		cout << "valid age is between " << MIN_AGE << " - " << MAX_AGE << ", cannot create a person " << age << " years old." << endl;
	}

};

#endif //__INVALID_AGE_EXCEPTION