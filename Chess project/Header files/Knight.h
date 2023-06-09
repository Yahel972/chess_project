#pragma once
#include "Piece.h"
#include "King.h"

class Knight: public Piece
{
public:
	Knight(char type, std::string _currPlace);
	virtual ~Knight();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board, bool dontRecurse = false) const override;
	virtual bool canAvoidCheck(const Board& board) const override;
};
