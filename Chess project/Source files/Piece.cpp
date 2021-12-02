#include "Piece.h"

// constructor
Piece::Piece(char type)
{
    this->_type = type;
}

// destructor (using default)
Piece::~Piece()
{
}

// type getter
char Piece::getType() const
{
    this->_type;
}
