#include "personException.h"




const void invalidAgeException::show() const
	{
		cout << "valid age is between " << MIN_AGE << " - " << MAX_AGE << ", cannot create a person " << age << " years old." << endl;
	}

const void invalidNameException::show() const
	{
		cout << "Name cannot be an empty string" << endl;
	}
