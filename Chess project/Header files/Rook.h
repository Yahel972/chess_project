#pragma once
#include "Piece.h"

class Rook: public Piece
{
public:
	Rook(char type);
	virtual ~Rook();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board) const;
};
