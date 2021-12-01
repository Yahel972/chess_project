#pragma once
#include "Piece.h"

class Knight: Piece
{
public:
	Knight();
	virtual ~Knight();
	virtual int checkMove(const std::string& currentPlace, const std::string& newPlace, const Board& board) const;
};
