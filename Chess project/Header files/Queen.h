#pragma once
#include "Rook.h"
#include "Bishop.h"

class Queen: public Rook, public Bishop
{
public:
	Queen(char type, std::string _currPlace);
	virtual ~Queen();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board, bool dontRecurse = false) const override;
	virtual bool canAvoidCheck(const Board& board) const override;
};
