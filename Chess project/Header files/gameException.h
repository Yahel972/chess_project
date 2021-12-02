#pragma once
#include <exception>

class GameException: public std::exception
{
protected:
	const char* _type;
public:
	GameException(const char* type);
	virtual const char* what() const;
};

