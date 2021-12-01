#pragma once
#include "Piece.h"

class Rook: Piece
{
public:
	Rook();
	virtual ~Rook();
	virtual int checkMove(const std::string& currentPlace, const std::string& newPlace, const Board& board) const;
};
