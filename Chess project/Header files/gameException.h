#pragma once
#include <exception>

class GameException: public std::exception
{
private:
	char* type;
public:
	GameException(const char* type);
	virtual const char* what() const;
};

