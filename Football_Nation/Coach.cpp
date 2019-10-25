#include "coach.h"

const char* roles[] = { "Striker", "Defender", "GoalKepper", "Midfielder" };

Coach::Coach(const string& name, int age, const string& nationality, Role type, Team * currentTeam) :
	Person(name, age, nationality)
{
	setType(type);
	setTeam(currentTeam);
}

Coach::Coach(const Coach& other):
	Person(other.name, other.age, other.nationality)
{
	setType(other.type);
	setTeam(other.currentTeam);
}

ostream& operator<<(ostream& os, const Coach& c)
{
	const char* teamName;
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
			currentTeam->removeCoach(this);
		currentTeam = team;
		if (currentTeam != nullptr)
		{
			currentTeam->addCoach(this);  // add coach to team
		}
	}
}