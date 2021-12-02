#pragma once
#include "Piece.h"

class Queen: public Piece
{
public:
	Queen(char type);
	virtual ~Queen();
	virtual int checkMove(const std::string& currentPlace, const std::string& newPlace, const Board& board) const;
};
