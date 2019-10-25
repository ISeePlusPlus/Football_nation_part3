#ifndef __PERSON_H
#define __PERSON_H
#pragma warning(disable:4996)
#include <iostream>
#include "NullPointerException.h"
using namespace std;

const int NAME_SIZE = 30;
const int MIN_AGE = 17;
const int MAX_AGE = 120;

class Person
{
protected:
	string name;//[NAME_SIZE];
	int age;
	char* nationality; //[NAME_SIZE] ;
	Person(const Person& other);
	virtual ~Person();
	const Person& operator=(const Person& other);

public:
	Person(const char* name, int age, const char* nationality);

	//virtual char* defineRoles() = 0;
	//TODO think about this?

	char* getName() const;
	int getAge() const;
	char* getNationality() const;

	void setName(const char* newName);
	bool setAge(int newAge);
	void setNationality(const char* newNationality);
};

class invalidAgeException
{
	int age;

public:
	invalidAgeException(int age) : age(age) {}

	void show() const
	{
		cout << "valid age is between " << MIN_AGE << " - " << MAX_AGE << ", cannot create a person " << age << " years old." << endl;
	}

};

class invalidNameException
{
public:
	invalidNameException() { }

	void show() const
	{
		cout << "Name cannot be an empty string" << endl;
	}
};

#endif //__PERSON_H


	

