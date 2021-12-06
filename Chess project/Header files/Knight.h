#pragma once
#include "Piece.h"

class Knight: public Piece
{
public:
	Knight(char type, std::string _currPlace);
	virtual ~Knight();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board) const;
};
