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
public:
	League(const string& name, int numberOfTeams); //in the constructor, number of teams must be the size of team array!
	virtual ~League();
	void addTeam(Team& team) throw(NoSpaceException);
	void setNumberOfReferees(int numberOfreferees); 
	void addReferee(Referee& referee) throw(NoSpaceException); //add a referee only if there is a room in the array.
	void startSeason() throw (LeagueException);
	const Fixture& playFixture() throw (LeagueException);
	void showLeadingTeam() const;
	void showLosingTeam() const;
	void showLeadingScorer();
	void showMostActiveReferee() const;
	bool isEnded();
	void rotate();
	int getNumberOfTeams() const;
	vector<Team>& getTeams();
	vector<Fixture>& getFixtures();
	void sortTeams(); //sort the teams by points (std::sort)
	friend ostream& operator<<(ostream& os, const League& league);
	Team& getWinner();

	int getPlayedFixtures() const;
	void addPlayedFixture();
//	void setName(const string& name);

private:
	string name;
	int numberOfTeams;
	int numberOfReferees;
	//	int teamIndex;
	//	int refIndex;
	vector<Team> teams;
	vector<Team> rotationTeams;
	vector<Team> leaderBoard;
	//vector<Team> rotationTeams;         //no longer needed
	vector<Referee> referees;
	int numberOfFixtures;
	int playedFixtures;
	vector<Fixture> fixtures;

	//League(const League& other);                            //no longer needed
	//const League& operator=(const League& other) = delete; 
};

#endif // !__LEAGUE_H

