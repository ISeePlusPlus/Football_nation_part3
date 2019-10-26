#ifndef __INVALID_NAME_EXCEPTION
#define __INVALID_NAME_EXCEPTION


class InvalidNameException
{
public:
	InvalidNameException() {};
	const void show() const
	{
		cout << "Name cannot be an empty string" << endl;
	}

};

#endif //__INVALID_NAME_EXCEPTION