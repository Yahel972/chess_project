#pragma once
#include "Piece.h"

class Pawn: Piece
{
public:
	Pawn();
	virtual ~Pawn();
	virtual int checkMove(const std::string& currentPlace, const std::string& newPlace, const Board& board) const;
};
