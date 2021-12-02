#include "gameException.h"

GameException::GameException(const char* type): _type(type) {}

const char* GameException::what() const
{
    return _type;
}
