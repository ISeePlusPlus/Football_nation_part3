#include "NullPointerException.h"

NullPointerException::NullPointerException(const string& var)
{
	this->variable = var;
}

void NullPointerException::show() const
{
	cout << "The variable " << variable << " cannot be nullptr!" << endl;
}