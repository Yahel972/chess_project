#pragma once
#include "Piece.h"

class Queen: public Piece
{
public:
	Queen(char type);
	virtual ~Queen();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board) const;
};
