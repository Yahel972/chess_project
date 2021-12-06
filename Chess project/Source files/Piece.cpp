#include "Piece.h"
#include "gameExceptions.h"
#define VALID_PIECES std::string("rnbkqp#PRNBKQ")
// constructor
Piece::Piece(char type, std::string _currPlace): _type(type), _currPlace(_currPlace)
{
    if (VALID_PIECES.find(type) == std::string::npos)
    {
        throw TypeException("Invalid piece type!");
    }
}

// destructor (using default)
Piece::~Piece() {}

// type getter
char Piece::getType() const
{
    return this->_type;
}

std::string Piece::getCurrPlace() const
{
    return _currPlace;
}

void Piece::setCurrPlace(std::string newVal)
{
    _currPlace = newVal;
}
