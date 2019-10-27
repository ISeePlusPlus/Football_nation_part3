#ifndef __FIXTURE_H
#define __FIXTURE_H
#include "match.h"

class Fixture
{

private:
	bool hasPlayed;
	int gamesInFixture;
	int number;
	Match** matches;
public:
	Fixture(int gamesInFixture, int number, Match** matches);
//	~Fixture();
//	Fixture(const Fixture& other);
	void setHasPlayed(bool value);
	int getGamesInFixture() const;
	int getFixtureNumber() const;
	Match** getMatchesInFixture();

	

	friend ostream& operator<<(ostream& os,const Fixture& fixture);

};
#endif // !__FIXTURE_H

