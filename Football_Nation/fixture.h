#ifndef __FIXTURE_H
#define __FIXTURE_H
#include "match.h"
#include "LinkedList.h"

class Fixture
{

private:
	bool hasPlayed;
	int gamesInFixture;
	int number;
	LinkedList<Match> matches;
	//Match** matches;
public:
	Fixture(int gamesInFixture, int number, LinkedList<Match> matches);
//	~Fixture();
//	Fixture(const Fixture& other);
	void setHasPlayed(bool value);
	int getGamesInFixture() const;
	int getFixtureNumber() const;
	LinkedList<Match> getMatchesInFixture();

	

	friend ostream& operator<<(ostream& os,const Fixture& fixture);

};
#endif // !__FIXTURE_H

