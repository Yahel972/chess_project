#pragma once
#include "Piece.h"

class Queen: public Piece
{
public:
	Queen(char type, std::string _currPlace);
	virtual ~Queen();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board) const override;
};
