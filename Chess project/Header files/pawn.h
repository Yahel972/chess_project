#pragma once
#include "Piece.h"

class Pawn: public Piece
{
public:
	Pawn(char type);
	virtual ~Pawn();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board) const;
};
