#include "person.h"

/*
#include "Mood.h"
#include "Neutral.h"
#include "Happy.h"
#include "Unhappy.h"
*/

Person::Person(const string& name, int age, const string& nationality)
{
	try 
	{
		setName(name);
		setAge(age);
		setNationality(nationality);
	}

	catch (InvalidAgeException& e) 
	{
		e.show();
		throw e;
	}
	catch (InvalidNameException& e)
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

/*
Person::Person(const Person& other)      // For mood assingment
{
	setName(other.name);
	setAge(other.age);
	setNationality(other.nationality);

	cout << typeid(*other.mood).name() << endl;

	if (typeid(*other.mood).name() == "class Neutral")
	{
		mood->neutral(*this);
	}
}


Person::~Person()
{
	delete mood;
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

void Person::setName(const string& newName) throw (InvalidNameException)
{
	newName.empty() ? throw InvalidNameException() : 0;

	this->name = newName;
}
void Person::setAge(int newAge) throw (InvalidAgeException)
{
	if (newAge < MIN_AGE || newAge > MAX_AGE)
	{
		throw InvalidAgeException(newAge);
	}
	age = newAge;
}

void Person::setNationality(const string& newNationality) throw (NullPointerException)
{
	newNationality.empty() ? throw NullPointerException("Person::nationality") : 0;
	this->nationality = newNationality;
}

/*
void Person::setMood(Mood* mood)
{
	this->mood = mood;
}

Mood* Person::getMood() const
{
	return mood;
}

void Person::happy()
{
	mood->happy(*this);
}

void Person::unhappy()
{
	mood->unhappy(*this);
}

void Person::neutral()
{
	mood->neutral(*this);
}

*/