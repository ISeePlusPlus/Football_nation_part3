#include "coach.h"

const char* roles[] = { "Striker", "Defender", "GoalKepper", "Midfielder" };

Coach::Coach(const string& name, int age, const string& nationality, Role type, Team * currentTeam) :
	Person(name, age, nationality)
{
	setType(type);
	setTeam(currentTeam);
}

Coach::Coach(const Coach& other): Person(other.name, other.age, other.nationality), currentTeam(nullptr)
{
	setType(other.type);
	//setTeam(nullptr);
}

ostream& operator<<(ostream& os, const Coach& c)
{
	string teamName;
	if (c.getCurrentTeam() == nullptr)
		teamName = "None";
	else
		teamName = c.getCurrentTeam()->getName();
	os << "Name: " << c.name << "," << "\tAge: " << c.age << ", Nationality: " << c.nationality << "\t\tRole: " << roles[(int)c.getType()] 
		<< ", Team: " << teamName << endl;
	return os;
}

Role Coach::getType() const {return type; }
Team* Coach::getCurrentTeam() const {return currentTeam;}

void Coach::setType(Role type)
{
	this->type = type;
}

void Coach::setTeam(Team* team)
{
	if (currentTeam != team)
	{
		if (currentTeam != nullptr)
			currentTeam->removeCoach(*this);
		currentTeam = team;
		if (currentTeam != nullptr)
		{
			currentTeam->addCoach(*this);  // add coach to team
		}
	}
}

bool Coach::operator==(const Coach& other) const
{
	if (this->getType() == other.getType() && this->age == other.age && this->name == other.name && this->nationality == other.nationality)
		return true;
	else
		return false;
}