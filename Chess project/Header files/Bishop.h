#pragma once
#include "Piece.h"

class Bishop: public Piece
{
public:
	Bishop(char type);
	virtual ~Bishop();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board) const;
};
