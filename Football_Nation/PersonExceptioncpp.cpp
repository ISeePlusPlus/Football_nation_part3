#include "personException.h"




const void InvalidAgeException::show() const
	{
		cout << "valid age is between " << MIN_AGE << " - " << MAX_AGE << ", cannot create a person " << age << " years old." << endl;
	}

const void InvalidNameException::show() const
	{
		cout << "Name cannot be an empty string" << endl;
	}
