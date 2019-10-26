#include "fixture.h"

Fixture::Fixture(int gamesInFixture, int number, LinkedList<Match> matches) :
	gamesInFixture(gamesInFixture), number(number), matches(matches), hasPlayed(false)
{

}

int Fixture::getGamesInFixture() const
{
	return gamesInFixture;
}

int Fixture::getFixtureNumber() const
{
	return number;
}

LinkedList<Match> Fixture::getMatchesInFixture()
{
	return matches;
}

void Fixture::setHasPlayed(bool value)
{
	this->hasPlayed = value;
}

ostream& operator<<(ostream& os, const Fixture& fixture)
{
	os << "Fixture #" << fixture.number << endl;
	for (int i = 0; i < fixture.gamesInFixture; i++)
	{
		os << fixture.matches.get(i);
		if (fixture.hasPlayed == true) 
		{
			os << " || result:  " << fixture.matches.get(i).getResult(0) << ":" << fixture.matches.get(i).getResult(1)<< endl;
		}
	}
	return os;
}

