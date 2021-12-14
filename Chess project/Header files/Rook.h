#pragma once
#include "Piece.h"

class Rook: virtual public Piece
{
public:
	Rook(char type, std::string _currPlace);
	virtual ~Rook();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board, bool dontRecurse=false) const override;
};
