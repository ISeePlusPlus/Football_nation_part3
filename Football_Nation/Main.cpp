#include <iostream>
using namespace std;
#include <fstream>

#include "referee.h"
#include "player.h"
#include "coach.h"
#include "manager.h"
#include "referee.h"
#include "league.h"
#include "fixture.h"
#include "coach_player.h"
#include "LinkedList.h"

League * readLeague(ifstream& inputFile);
Team * readTeam(ifstream& inputFile);
Player * readPlayer(ifstream& inputFile);
Coach * readCoach(ifstream& inputFile);
Manager * readManager(ifstream& inputFile);
Referee * readReferee(ifstream& inputFile);

int main()
{
	/*
	Referee ref("Cpp", 25, "Language", 1, 0);
	Player messi("Messi", 32, "Spain", 40, 30, 10, 0, 10000, (Role)0);
	Player ronaldo("Ronaldo", 34, "Portugal", 90, 5, 10, 0, 9000, (Role)0);
	Player zlatan("Zlatan", 39, "God", 100, 20, 10, 0, 8000, (Role)0);
	Player m("AAA", 20, "Something", 20, 20, 20, 0, 1000, (Role)2);
	Coach z("Zidan", 40, "French", (Role)2, nullptr);
	CoachPlayer strange("Dr. Strange", 30, "British", z, messi);
	
	Manager a("Arcadi", 60, "Russian", 10);
	Team t1("Hapoel", &a);
	++messi;
	t1.addCoach(&z);
	t1.setManager(nullptr);
	t1.setManager(&a);
	t1.addPlayer(&messi);
	t1.addPlayer(&ronaldo);
	t1.addPlayer(&strange);
	t1.addPlayer(&zlatan);
	t1.addPlayer(&m);

	t1.addToLineup(&messi);
	t1.addToLineup(&ronaldo);
	t1.addToLineup(&strange);
	t1.addToLineup(&zlatan);
	t1.addToLineup(&m);

	Player mich("Michael Jordan", 50, "USA", 10, 10, 50, 0, 7000, Role::Striker);
	Player zehavi("Zehavi", 30, "Israeli", 50, 30, 20, 0, 4000, (Role)2);
	Player ooo1("Who", 30, "As", 40, 40, 40, 0, 4000, (Role)3);
	Player ooo2("Who2", 30, "As", 40, 40, 40, 0, 4000, (Role)3);
	Player ooo3("Who3", 30, "As", 40, 40, 40, 0, 4000, (Role)3);
	Manager b("E.T", 500, "Alien", 400);
	Team t2("Macabbi", &b);
	Coach coach("Mr. coach", 30, "Coacher", (Role)2, nullptr);
	t2.addCoach(&coach);
	t2.addPlayer(&mich);
	t2.addPlayer(&zehavi);
	t2.addPlayer(&ooo1);
	t2.addPlayer(&ooo2);
	t2.addPlayer(&ooo3);

	t2.addToLineup(&mich);
	t2.addToLineup(&zehavi);
	t2.addToLineup(&ooo1);
	t2.addToLineup(&ooo2);
	t2.addToLineup(&ooo3);

	cout << t1 <<endl;
	cout << t2 << "\n\n---------------------------------" << endl;

	Team** teams  = new Team*[2];
	teams[0] = &t1;
	teams[1] = &t2;

	Referee** refs = new Referee * [1];
	refs[0] = &ref;

	League lig("League of Legends", 2, teams, 1, refs);

	lig.startSeason();
	cout << lig << endl;
	delete[] teams;
	
	int val = 5;
	int val2 = 584;
	int val3 = 8;
	LinkedList<Player> list(messi);
	list.insertToEnd(ronaldo);
	list.insertToEnd(zlatan);
	list.insertToEnd(strange);
	//list.deleteEnd();
	//list.deleteEnd();
	//list.deleteStart();
	cout << list;
	cout << "\n\n" << list.get(3);
	system("pause");
	*/
	ifstream inputFile("League.txt");
	League* league = readLeague(inputFile);


	// adding the players from bench to the line up, because PlayMatch() cannot work when the lineup is empty.
	for (int i = 0; i < league->getNumberOfTeams(); i++)
	{
		for (int j = 0; j < LINEUP_SIZE; j++)
		{
			try 
			{
				league->getTeams().at(i).addToLineup(&league->getTeams().at(i).getBench().at(0));
			}
			catch (NullPointerException & e)
			{
				e.show();
			}
			catch (NoSpaceException & e)
			{
				e.show();
			}
		}
		//cout << *league->getTeams()[i];
	}
	/*
	 *start season (create season fixtures)
	 *create matches and assign referees for each match
	 */
	try 
	{
		league->startSeason();
	}
	catch (LeagueException& e)
	{
		e.show();
	}
	/*
	 *Play matches until the endF of the season
	 *	-assign the match number of goals (random)
	 *	-for each goal u assign u will need to assign (random) player that scored
	 *	-display the fixture's matches results
	 *	-every fixture played u should increment number of fixtures played
	 */
	do
	{
		try
		{
			Fixture fixture = league->playFixture();
			cout << fixture;
		}
		catch (LeagueException& e)
		{
			e.show();
		}
	} while (!league->isEnded());
	
	//end season
	//show League Table
	//league->sortTeams();
	cout << *league << endl;
	
	//show leading team(team)
	league->showLeadingTeam();
	//show the loosing team(team)
	league->showLosingTeam();
	//show the leading scorer(player)
	league->showLeadingScorer();
	//show the ref that played the most matches
	league->showMostActiveReferee();
	
	inputFile.close();
	system("pause");
	return 0;
}

League* readLeague(ifstream& inputFile)
{
	int numberOfTeams;
	int numberOfreferees;
	string name;
	League* newLeague;

	/*Get League name*/
	inputFile >> name;
	/*Get number of teams*/
	inputFile >> numberOfTeams;
	newLeague = new League(name, numberOfTeams);

	for (int i = 0; i < numberOfTeams; i++)
	{
		Team* team = readTeam(inputFile);
		try
		{
			newLeague->addTeam(team);
		}
		catch (NullPointerException & e)
		{
			e.show();
		}
		catch (NoSpaceException & e)
		{
			e.show();
		}
	}

	/*Get number of referees*/
	inputFile >> numberOfreferees;
	newLeague->setNumberOfReferees(numberOfreferees);
	for (int i = 0; i < numberOfreferees; i++)
	{
		Referee* referee = readReferee(inputFile);
		try 
		{
			newLeague->addReferee(referee);
		}
		catch (NullPointerException & e)
		{
			e.show();
		}
		catch (NoSpaceException & e)
		{
			e.show();
		}

	}

	return newLeague;
}

Team* readTeam(ifstream& inputFile)
{
	int numberOfPlayers, numberOfCoaches;
	char name[NAME_SIZE];

	/*Get team name*/
	inputFile >> name;
	/*Get number of players*/
	inputFile >> numberOfPlayers;

	Team* newTeam = new Team(name);
	for (int i = 0; i < numberOfPlayers; i++)
	{
		Player* player = readPlayer(inputFile);
		try
		{
			newTeam->addPlayer(player);
		}
		catch (NullPointerException & e)
		{
			e.show();
		}
		catch (NoSpaceException & e)
		{
			e.show();
		}
	}

	/*Get number of coaches*/
	inputFile >> numberOfCoaches;

	for (int i = 0; i < numberOfCoaches; i++)
	{
		Coach* coach = readCoach(inputFile);
		try
		{
		newTeam->addCoach(coach);
		}
		catch (NullPointerException & e)
		{
			e.show();
		}
		catch (NoSpaceException & e)
		{
			e.show();
		}

	}

	Manager* manager = readManager(inputFile);
	newTeam->setManager(manager);
	return newTeam;
}

Player* readPlayer(ifstream& inputFile)
{
	char name[NAME_SIZE], nationality[NAME_SIZE];
	int age, attack, defence, goalkeeping, goalScored, value, role;

	/*Get Player attributes*/
	inputFile >> name >> age >>
		nationality >> attack >>
		defence >> goalkeeping >>
		goalScored >> value >> role;

	return new Player(name, age, nationality, attack, defence, goalkeeping, goalScored, value, (Role) role);
}

Coach* readCoach(ifstream& inputFile)
{
	char name[30], nationality[30];
	int age, type;

	/*Get Coach attributes*/
	inputFile >> name >> age >> nationality >> type;

	return new Coach(name, age, nationality, (Role) type);
}

Manager* readManager(ifstream& inputFile)
{
	char name[NAME_SIZE], nationality[NAME_SIZE];
	int age, yearsOfExperience;

	/*Get manager attributes*/
	inputFile >> name >> age >> nationality >> yearsOfExperience;

	return new Manager(name, age, nationality, yearsOfExperience);
}

Referee* readReferee(ifstream& inputFile)
{
	char name[NAME_SIZE], nationality[NAME_SIZE];
	int age, rating;

	/*Get referee attributes*/
	inputFile >> name >> age >> nationality >> rating;

	return new Referee(name, age, nationality, rating, 0);
}