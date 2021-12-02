#include "Piece.h"
#include "gameExceptions.h"
#define VALID_PIECES std::string("rnbkqp#PRNBKQ")
// constructor
Piece::Piece(char type): _type(type)
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
