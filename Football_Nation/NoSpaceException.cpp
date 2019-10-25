#include "NoSpaceException.h"

NoSpaceException::NoSpaceException(const string& name, int index) : index(index)
{
	this->structName = name;
}

void NoSpaceException::show() const
{
	cout << "There is no space in index #" << index << " at " << structName << endl;
}