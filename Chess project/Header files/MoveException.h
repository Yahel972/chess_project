#pragma once
#include "gameException.h"
class MoveException: public GameException
{
public:
	MoveException(const char* type, gameCodes errorCode);
	virtual const char* what() const;
private:
	gameCodes _errorCode;
};
