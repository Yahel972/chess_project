#pragma once
#include "Piece.h"

class King: public Piece
{
public:
	King(char type);
	virtual ~King();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board) const;
};
