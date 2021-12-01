#pragma once
#include "Piece.h"

class Queen: Piece
{
public:
	Queen();
	virtual ~Queen();
	virtual int checkMove(const std::string& currentPlace, const std::string& newPlace, const Board& board) const;
};
