#include "personException.h"


class PersonException
{

};

class invalidAgeException : public PersonException
{
	int age;

public:
	invalidAgeException(int age) : age(age) {}

	virtual const void show() const
	{
		cout << "valid age is between " << MIN_AGE << " - " << MAX_AGE << ", cannot create a person " << age << " years old." << endl;
	}

};

class invalidNameException : public PersonException
{
public:
	invalidNameException() { }

	virtual const void show() const
	{
		cout << "Name cannot be an empty string" << endl;
	}
};