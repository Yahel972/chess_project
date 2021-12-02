#include "TypeException.h"

TypeException::TypeException(const char* type): GameException(type) {}

const char* TypeException::what() const
{
    return _type;
}