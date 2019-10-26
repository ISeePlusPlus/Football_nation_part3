#include "player.h"

const char* playerRoles[] = { "Striker", "Defender", "GoalKepper", "Midfielder" };

Player::Player(const string& name, int age, const string& nationality, int attack, int defence, int goalkeeping, int goalScored, int value,
	Role role) : Person(name, age, nationality), attack(attack), defence(defence), goalkeeping(goalkeeping), goalScored(goalScored), value(value),
	role(role), currentTeam(nullptr)
{
}

Player::Player(const Player& other) : Person (other.name, other.age, other.nationality), attack(other.attack), defence(other.defence), goalkeeping(other.goalkeeping), goalScored(other.goalScored),
value(other.value), role(other.role), currentTeam(other.currentTeam)
{
}

int Player::getAttack() const
{
	return attack;
}

int Player::getDefence() const
{
	return defence;
}

int Player::getGoalkeeping() const
{
	return goalkeeping;
}

int Player::getGoalScored() const
{
	return goalScored;
}

int Player::getValue() const
{
	return value;
}

Role Player::getRole() const
{
	return role;
}

Team* Player::getTeam() const
{
	return currentTeam;
}

int Player::getTotalStats() const
{
	return 0;
}

void Player::setAttack(int atk)
{
	attack = atk;
}

void Player::setDefence(int def)
{
	defence = def;
}

void Player::setGoalkeeping(int goalkeeping)
{
	goalkeeping = goalkeeping;
}

void Player::setValue(int val)
{
	value = val;
}

void Player::setRole(Role role)
{
	this->role = role;
}

void Player::setTeam(Team* team)
{
	this->currentTeam = team;
}

void Player::show() const
{

}

ostream& operator<<(ostream& os, const Player& player)
{
	string teamName;
	if (player.currentTeam == nullptr)
		teamName = "None";
	else
		teamName = player.currentTeam->getName();
	os << "Name: " << player.name << "," << "\tAge: " << player.age << ", Nationality: " << player.nationality << "\t\t {| Atk/Def/Gkp: " << player.attack << "/" << player.defence << "/" << player.goalkeeping
		<< " |} Role: " << playerRoles[(int)player.getRole()] << ", Value: " << player.value << ", Total goals: " << player.goalScored << ", Team: " << teamName << endl;
	return os;
}

bool Player::operator==(const Player& other) const
{
	if (this->age == other.age && this->name == other.name && this->nationality == other.nationality)
		return true;
	else
		return false;
}

const Player& Player::operator++()
{
	++goalScored;
	return *this;
}

bool Player::operator>=(const Player& player) const
{
	if (this->goalScored >= player.getGoalScored())
		return true;
	else
		return false;
}