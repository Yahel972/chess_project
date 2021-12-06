#include "MoveException.h"

const char* errors[] = { "srcInvalid", "dstInvalid", "invalidCheckOnSelf", "invalidIndex", "invalidMove", "invalidSrcIsDst" };

MoveException::MoveException(const char* type, gameCodes errorCode): GameException(type), _errorCode(errorCode) {}

gameCodes MoveException::getErrorCode() const
{
    return _errorCode;
}

const char* MoveException::getErrorMessage() const
{
    return errors[_errorCode];
}