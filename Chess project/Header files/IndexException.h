#pragma once
#include "gameException.h"
class IndexException: public GameException
{
public:
	IndexException(const char* type);
};

