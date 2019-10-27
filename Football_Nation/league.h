#ifndef __LEAGUE_H
#define __LEAGUE_H

#pragma warning(disable:4996)

#include "team.h"
#include "referee.h"
#include "fixture.h"
#include "player.h"
#include "NullPointerException.h"
#include "NoSpaceException.h"
#include "leagueException.h"
#include <algorithm>

class Team;
class Referee;
class Fixture;
class League

{

private:
	string name;
	int numberOfTeams;
	int numberOfReferees;
//	int teamIndex;
//	int refIndex;
	vector<Team> teams;
	vector<Team> rotationTeams;         //to rotate while keeping the original team order in teams
	vector<Referee> referees;
	int numberOfFixtures;
	int playedFixtures;
	Fixture** fixtures;

	//League(const League& other);                            //no longer needed
	//const League& operator=(const League& other) = delete; 
public:
	League(const string& name, int numberOfTeams,
		vector<Team> teams, vector<Referee> referees,
		 int numberofreferees = 0); //in the constructor, number of teams must be the size of team array!

	virtual ~League();
	void addTeam(Team* team) throw(NoSpaceException);
	void setNumberOfReferees(int numberOfreferees); 
	void addReferee(Referee* referee) throw(NoSpaceException); //add a referee only if there is a room in the array.
	void startSeason() throw (LeagueException);
	const Fixture& playFixture() throw (LeagueException);
	void showLeadingTeam() const;
	void showLosingTeam() const;
	void showLeadingScorer() const;
	void showMostActiveReferee() const;
	bool isEnded();
//	void rotate();
	int getNumberOfTeams() const;
	vector<Team> getTeams() const;
	void sortTeams(); //sort the teams by points (std::sort)
	friend ostream& operator<<(ostream& os, const League& league);

	int getPlayedFixtures() const;
	void addPlayedFixture();
//	void setName(const string& name);
};
/*
class oddTeamNumberException 
{
public:

};
*/
#endif // !__LEAGUE_H

