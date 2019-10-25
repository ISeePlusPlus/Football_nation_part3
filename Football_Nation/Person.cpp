#include "person.h"


Person::Person(const string& name, int age, const string& nationality)
{
	try 
	{
		setName(name);
		setAge(age);
		setNationality(nationality);
	}

	catch (invalidAgeException& e) 
	{
		e.show();
		throw e;
	}
	catch (invalidNameException& e)
	{
		e.show();
		throw e;
	}
	catch (NullPointerException& e)
	{
		e.show();
		throw e;
	}

}

const Person& Person::operator=(const Person& other)
{
	setName(other.name);
	setAge(other.age);
	setNationality(other.nationality);

	return *this;
}

Person::Person(const Person& other)
{
	*this = other;
}
/*
Person::~Person()
{
	delete []name;
	delete []nationality;
}
*/
//Getters

const string& Person::getName() const { return name; }
int Person::getAge() const { return age; }
const string& Person::getNationality() const{ return nationality; }

//Setters

void Person::setName(const string& newName) throw (invalidNameException)
{
	newName.empty() ? throw invalidNameException() : 0;

	this->name = name;
}
bool Person::setAge(int newAge) throw (invalidAgeException)
{
	if (newAge < MIN_AGE || newAge > MAX_AGE)
	{
		throw invalidAgeException(newAge);
	}
	age = newAge;
	return true;
}
void Person::setNationality(const string& newNationality) throw (NullPointerException)
{
	newNationality.empty() ? throw NullPointerException("Person::nationality") : 0;
	this->nationality = nationality;
}

