#ifndef __PERSON_H
#define __PERSON_H
#pragma warning(disable:4996)
#pragma warning(disable:4290)

using namespace std;

const int NAME_SIZE = 30;
const int MIN_AGE = 17;
const int MAX_AGE = 120;

#include <iostream>
#include "NullPointerException.h"
#include "InvalidAgeException.h"
#include "InvalidNameException.h"


class Mood;

class Person
{
protected:
	Mood* mood;
	string name;//[NAME_SIZE];
	int age;
	string nationality; //[NAME_SIZE] ;
//	Person(const Person& other);
//	virtual ~Person();
//	const Person& operator=(const Person& other);

public:
	Person(const string& name, int age, const string& nationality);
	~Person();

	const string& getName() const;
	int getAge() const;
	const string& getNationality() const;

	void setName(const string& newName) throw (InvalidNameException);
	void setAge(int newAge) throw (InvalidAgeException);
	void setNationality(const string& newNationality) throw (NullPointerException);

	void setMood(Mood* mood);
	Mood* getMood() const;
	void happy();
	void unhappy();
	void neutral();
};


#endif //__PERSON_H


	

