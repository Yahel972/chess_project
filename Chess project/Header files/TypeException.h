#pragma once
#include "gameException.h"

class TypeException: public GameException
{
public:
	TypeException(const char* type);
	virtual const char* what() const;
};