#pragma once
#include "Piece.h"

class King: Piece
{
public:
	King();
	virtual ~King();
	virtual int checkMove(const std::string& currentPlace, const std::string& newPlace, const Board& board) const;
};
