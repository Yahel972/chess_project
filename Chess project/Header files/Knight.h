#pragma once
#include "Piece.h"

class Knight: public Piece
{
public:
	Knight(char type);
	virtual ~Knight();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board) const;
};
