#ifndef __LEAGUE_H
#define __LEAGUE_H

#pragma warning(disable:4996)

#include "team.h"
#include "referee.h"
#include "fixture.h"

class Team;
class Referee;
class Fixture;
class League
{

private:
	char* name;
	int numberOfTeams;
	int numberOfReferees;
	Team** teams;
	Referee** referees;
	int numberOfFixtures;
	int playedFixtures;
	Fixture** fixtures;

public:
	League(const char* name, int numberOfTeams,
		Team** teams = nullptr, int numberofreferees = 0,
		Referee** referees = nullptr, int numberOfFixtures = 0); //in the constructor, number of teams must be the size of team array!

	~League();
	void addTeam(Team * team);
	void setNumberOfReferees(int numberOfreferees);
	void addReferee(Referee * referee);
	void startSeason();
	const Fixture& playFixture();
	void showLeadingTeam() const;
	void showLoosingTeam() const;
	void showLeadingScorer() const;
	void showMostActiveReferee() const;
	void show() const;
	bool isEnded();
};
#endif // !__LEAGUE_H

