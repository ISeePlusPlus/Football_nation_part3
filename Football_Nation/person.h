#ifndef __PERSON_H
#define __PERSON_H
#pragma warning(disable:4996)
#pragma warning(disable:4290)

#include <iostream>
#include "NullPointerException.h"
#include "personException.h"

using namespace std;

const int NAME_SIZE = 30;
const int MIN_AGE = 17;
const int MAX_AGE = 120;

class Person
{
protected:
	string name;//[NAME_SIZE];
	int age;
	string nationality; //[NAME_SIZE] ;

	Person(const Person& other);
//	virtual ~Person();
	const Person& operator=(const Person& other);

public:
	Person(const string& name, int age, const string& nationality);

	//virtual char* defineRoles() = 0;
	//TODO think about this?
	
	const string& getName() const;
	int getAge() const;
	const string& getNationality() const;

	void setName(const string& newName) throw (invalidNameException);
	void setAge(int newAge)  throw (invalidAgeException);
	void setNationality(const string& newNationality)  throw (NullPointerException);
	
};



#endif //__PERSON_H


	

