#include "referee.h"

const int Referee::arr[] = {3, 5, 15, 50, 100 };

Referee::Referee(const string& name, int age, const string& nationality, int rating = 0, int gamesPlayed = 0):
	Person(name,age,nationality)
{
	setGamesPlayed(gamesPlayed);
	//setRating();
}

const Referee& Referee::operator++()
{
	++gamesPlayed;
	return *this;
}

ostream& operator<<(ostream& os, const Referee& r)
{
	os << "Name: " << r.getName() << ", Age: " << r.getAge() << ", Nationality: " << r.getNationality() << ", Games played: " << r.getGamesPlayed() << ", Rating: " << r.getRating() << endl;
	return os;
}

int Referee::getGamesPlayed() const { return gamesPlayed; }
int Referee::getRating() const { return rating; }


void Referee::setGamesPlayed(int games) 
{
	this->gamesPlayed = games;
}

void Referee::setRating()
{
	if (getGamesPlayed() >= arr[MAX_RATING_POSITION])
	{
		this->rating = 5;
		return;
	}

	int counter = 0;
	while (this->getGamesPlayed() > Referee::arr[counter])
	{
		counter += 1;
		this->rating = counter;
	}
}

