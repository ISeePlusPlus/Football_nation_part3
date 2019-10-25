#ifndef __REFEREE_H
#define __REFEREE_H

#include "person.h"
#include <iostream>

const int MAX_RATING_POSITION = 4;

class Referee : public Person
{
private:
	static const int arr[];
	int gamesPlayed;
	int rating;

public:
	Referee(const string& name, int age, const string& nationality,int rating, int gamesPlayed);
	const Referee& operator++();
	friend ostream& operator<<(ostream& os, const Referee& r);
	Referee(const Referee& other) = delete;

	int getGamesPlayed() const;
	int getRating() const;

	void setGamesPlayed(int games);
	void setRating();

};


#endif //__REFEREE_H
