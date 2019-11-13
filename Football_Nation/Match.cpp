#include "match.h"
#include "player.h"
#include "referee.h"

#pragma warning(disable:4290)



Match::Match(Team& homeTeam, Team& awayTeam, Referee* referee) : homeTeam(homeTeam), awayTeam(awayTeam), referee(referee)
{
	stadium = homeTeam.getStadium();
}

Match::Match(const Match& other) : homeTeam(other.homeTeam), awayTeam(other.awayTeam), referee(other.referee), stadium(stadium)
{
}

void Match::playMatch() throw(PlayMatchException)
{
	//check that the team has enough players in the lineup
	if (homeTeam.getLineup().size() != LINEUP_SIZE)
		throw (PlayMatchException(&homeTeam, "Lineup is not full!"));
	if (awayTeam.getLineup().size() != LINEUP_SIZE)
		throw (PlayMatchException(&awayTeam, "Lineup is not full!"));
	//each team has the option to score goals in their turn to attack
	simulateAttack(homeTeam, awayTeam);
	simulateAttack(awayTeam, homeTeam);
	++(*this->referee); //adds a game to the referee
	this->referee->setRating();

	if (getResult(0) == getResult(1))        //Draw - add one point to each team
	{
		homeTeam.addPoints(1);
		awayTeam.addPoints(1);
	}
	else getResult(0) > getResult(1) ? homeTeam.addPoints(3) : awayTeam.addPoints(3);    //Either home or away teams won
	notifyAllRegistered();
}

void Match::simulateAttack(Team& attackingTeam, Team& defendingTeam) 
{
	int attackingScore = 0;
	int defendingScore = 0;
	int goalKeepingScore = 0;

	for (int i = 0; i < LINEUP_SIZE; i++) 
	{
		Player attPlayer = attackingTeam.getLineup().at(i);

		switch (attPlayer.getRole()) 
		{
			case (Role) 0:
				attackingScore += attPlayer.getAttack() + STRIKER_BONUS;                 //Player is a striker
				break;
			case (Role) 3:
				attackingScore += attPlayer.getAttack() + MID_BONUS;                     //Player is a midfielder
				break;
			default:
				attackingScore += attPlayer.getAttack();
		}


		Player defPlayer = defendingTeam.getLineup().at(i);

		switch (defPlayer.getRole())
		{
		case (Role) 1:
			defendingScore += defPlayer.getDefence() + DEFENDER_BONUS;                 //Player is a defender
			break;
		case (Role) 2:
			goalKeepingScore += defPlayer.getDefence() + defPlayer.getGoalkeeping(); //Player is a goalkepper
			break;
		case (Role) 3:
			defendingScore += defPlayer.getDefence() + MID_BONUS;                     //Player is a midfielder
			break;
		default:
			defendingScore += defPlayer.getDefence();
		}
	}
	for (int i = 0; i < ATTACK_ROUNDS; i++)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> random(MIN_RANDOM, MAX_RANDOM_ATTACK);
		std::uniform_int_distribution<std::mt19937::result_type> extra_round(0, 100);

		if ((int)random(rng) + attackingScore > defendingScore + goalKeepingScore)
		{
			attackingTeam.scoreGoal();
			&attackingTeam == &this->homeTeam ? this->result[0] += 1 : this->result[1] += 1;
		}
		if (extra_round(rng) < 18)
			i--;
	}
}

Team* Match::getWinnerTeam() const
{
	if (result[0] != result[1])
		if (result[0] > result[1])
			return &homeTeam;
		else
			return &awayTeam;
	return nullptr;
}


const Team& Match::getHomeTeam() const
{
	return homeTeam;
}

const Team& Match::getAwayTeam() const
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
	os << match.getHomeTeam().getName() << " VS " << match.getAwayTeam().getName() << "\tReferee: " << match.getReferee()->getName() << "\t";
	return os;
}

void Match::registerObserver(Observer* obs)
{
	gamblers.push_back(obs);
}

void Match::notifyAllRegistered()
{
	vector<Observer*>::iterator itrStart = gamblers.begin();
	vector<Observer*>::iterator itrEnd = gamblers.end();
	for (; itrStart != itrEnd; ++itrStart)
	{
		(*itrStart)->notify(this, this->getWinnerTeam());
	}
}

Building* Match::getStadium() const
{
	return stadium;
}