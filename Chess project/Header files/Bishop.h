#pragma once
#include "Piece.h"

class Bishop: virtual public Piece
{
public:
	Bishop(char type, std::string _currPlace);
	virtual ~Bishop();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board, bool dontRecurse = false) const override;
	virtual bool canAvoidCheck(const Board& board) const override;
};
