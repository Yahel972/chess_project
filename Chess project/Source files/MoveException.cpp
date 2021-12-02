#include "MoveException.h"

const char* errors[] = { "srcInvalid", "dstInvalid", "invalidCheckOnSelf", "invalidIndex", "invalidMove", "invalidSrcIsDst" };

MoveException::MoveException(const char* type, gameCodes errorCode): GameException(type), _errorCode(errorCode) {}

const char* MoveException::what() const
{
    return std::string(std::string(_type) + std::to_string(_errorCode) + " (" + errors[_errorCode] + ")").data();
}