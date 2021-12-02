#pragma once
#include <string>
#include "Board.h"

class Board;

class Piece
{
public:
	Piece(char type);
	virtual ~Piece();
	virtual int checkMove(const std::string& currentPlace, const std::string& newPlace, const Board& board) const = 0;
	char getType() const;

protected:
	char _type;
};

