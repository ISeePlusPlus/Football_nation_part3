#include "fixture.h"

Fixture::Fixture(int gamesInFixture, int number, vector<Match> matches) :
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

vector<Match>& Fixture::getMatchesInFixture()
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
		os << fixture.matches[i];
		if (fixture.hasPlayed == true)
		{
			const Match* match = &fixture.matches[i];
			os << " || result:  " << match->getResult(0) << ":" << match->getResult(1) << endl;
		}
	}
	return os;
}
