#pragma once
#include "Piece.h"

class Bishop: Piece
{
public:
	Bishop();
	virtual ~Bishop();
	virtual int checkMove(const std::string& currentPlace, const std::string& newPlace, const Board& board) const;
};
