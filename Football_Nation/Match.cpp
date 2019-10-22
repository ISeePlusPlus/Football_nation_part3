#include "match.h"
#include "player.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Match::Match(Team* homeTeam, Team* awayTeam, Referee* referee) : homeTeam(homeTeam), awayTeam(awayTeam), referee(referee)
{

}

void Match::playMatch()
{
	if (homeTeam->getLineupSize() != LINEUP_SIZE || awayTeam->getLineupSize() != LINEUP_SIZE) //check that the team has enough players in the lineup
		return;
	//each team has the option to score goals in their turn to attack
	simulateAttack(homeTeam, awayTeam);
	simulateAttack(awayTeam, homeTeam);
	++this->referee; //adds a game to the referee

	if (getResult(0) == getResult(1))        //Draw - add one point to each team
	{
		homeTeam->addPoints(1);
		awayTeam->addPoints(1);
	}
	else getResult(0) > getResult(1) ? homeTeam->addPoints(3) : awayTeam->addPoints(3);    //Either home or away teams won
}

void Match::simulateAttack(Team* attackingTeam, Team* defendingTeam) 
{
	int attackingScore = 0;
	int defendingScore = 0;
	int goalKeepingScore = 0;

	for (int i = 0; i < LINEUP_SIZE; i++) 
	{
		Player* attPlayer = attackingTeam->getLineup()[i];

		switch (attPlayer->getRole()) 
		{
			case (Role) 0:
				attackingScore += attPlayer->getAttack() + STRIKER_BONUS;                 //Player is a striker
				break;
			case (Role) 3:
				attackingScore += attPlayer->getAttack() + MID_BONUS;                     //Player is a midfielder
				break;
			default:
				attackingScore += attPlayer->getAttack();
		}

		Player* defPlayer = defendingTeam->getLineup()[i];

		switch (defPlayer->getRole())
		{
		case (Role) 1:
			defendingScore += defPlayer->getDefence() + DEFENDER_BONUS;                 //Player is a defender
			break;
		case (Role) 2:
			goalKeepingScore += defPlayer->getDefence() + defPlayer->getGoalkeeping(); //Player is a goalkepper
			break;
		case (Role) 3:
			defendingScore += defPlayer->getDefence() + MID_BONUS;                     //Player is a midfielder
			break;
		default:
			defendingScore += defPlayer->getDefence();
		}
	}

	for (int i = 0; i < ATTACK_ROUNDS; i++)
	{
		srand(time(NULL));
		int	random = rand() % 20;
		if (attackingScore + random > defendingScore + goalKeepingScore) 
		{
			attackingTeam->scoreGoal();
			attackingTeam == this->homeTeam ? this->result[0] += 1 : this->result[1] += 1;
		}
	}
}

Team* Match::getWinnerTeam() const
{
	if (result[0] != result[1])
		result[0] > result[1] ? homeTeam : awayTeam;
	return nullptr;
}


Team* Match::getHomeTeam() const
{
	return homeTeam;
}

Team* Match::getAwayTeam() const
{
	return awayTeam;
}

Referee* Match::getReferee() const
{
	return referee;
}

int Match::getResult(int index) const
{
	return result[index];
}

ostream& operator<<(ostream& os, const Match& match)
{
	os << "|| Home Team: " << match.getHomeTeam()->getName() << " VS " << "Away Team: " << " " << match.getAwayTeam()->getName() << "|| result:  " << match.getResult(0) << ":" << match.getResult(1) << endl;
	return os;
}