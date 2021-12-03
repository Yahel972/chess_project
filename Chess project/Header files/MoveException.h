#pragma once
#include "gameException.h"
#include "Piece.h"

class MoveException: public GameException
{
public:
	MoveException(const char* type, gameCodes errorCode);
	gameCodes getErrorCode() const;
	const char* getErrorMessage() const;
	virtual const char* what() const;
private:
	gameCodes _errorCode;
};

