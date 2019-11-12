#include "Gambler.h"

Gambler::Gambler(const string& name, int age, const string& nationality) : Person(name, age, nationality), prizeMoney(0)
{
}

void Gambler::notify(Match* match, Team* winner)
{
	if (bets.at(match) == winner)
	{
		prizeMoney += REWARD;
		cout << this->getName() << " has earned " << REWARD << " prizeMoney by betting on ";
		if (winner == nullptr)
			cout << "a Draw!" << endl;
		else
			cout << winner->getName() << "!" << endl;
	}
	cout << this->getName() << " has " << prizeMoney << " prizeMoney." << endl;
}

int Gambler::getPrizeMoney() const
{
	return prizeMoney;
}

void Gambler::placeBet(Match& match, Team& winner)
{
	bets.insert(pair<Match*, Team*>(&match, &winner));
}