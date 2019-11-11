#ifndef __MATCH_H
#define __MATCH_H
#include "team.h"
#include "PlayMatchException.h"
#include "Observer.h"

class Observer;

const int NUM_OF_RESULTS = 2 ;
const int ATTACK_ROUNDS = 3 ;
class Match
{

private:
	Team& homeTeam;
	Team& awayTeam;
	int result[NUM_OF_RESULTS] = { 0,0 }; // index 0 = home result, index 1 = away result.
	Referee* referee;
	void simulateAttack(Team& attackingTeam, Team& defendingTeam);

	vector<Observer*> gamblers;
	void notifyAllRegistered();

public:
	Match(Team& homeTeam, Team& awayTeam, Referee * referee);
	Match(const Match& other);
	void playMatch() throw(PlayMatchException); //move to private?

	Team* getWinnerTeam() const; //returns the winner team. If match has ended with a tie, returns nullptr
	const Team& getHomeTeam() const;
	const Team& getAwayTeam() const;
	Referee* getReferee() const;
	int getResult(int index) const;
	friend ostream& operator<<(ostream& os, const Match& fixture);

	void registerObserver(Observer* obs); //adding gamblers to observe the match's result
};

#endif // !__MATCH_H

