#include "Building.h"

void Building::add(const Floor& floor)
{
	floors.push_back(floor);
}

void Building::show() const
{
	cout << endl;
	vector<Floor>::const_iterator itrStart = floors.begin();
	vector<Floor>::const_iterator itrEnd = floors.end();
	for (; itrStart != itrEnd; ++itrStart)
	{
		char t = (itrStart)->getTexture();
		for (int i = 0; i < (itrStart)->getSize(); i++)
		{
			cout << t << t;
		}
		cout << "\n||" << (itrStart)->getName() << "||" << endl;
		for (int i = 0; i < (itrStart)->getSize(); i++)
		{
			cout << "==";
		}
		cout << endl;
	}
}