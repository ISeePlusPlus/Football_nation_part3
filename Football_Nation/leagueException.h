#include <iostream>

class LeagueException 
{
public:
	LeagueException(const std::string& reason):
		exceptionReason(reason){}

	virtual void show() const;

protected:
	const std::string exceptionReason;
	
};
