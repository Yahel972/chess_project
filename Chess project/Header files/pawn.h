#pragma once
#include "Piece.h"
#include "King.h"

class Pawn: public Piece
{
public:
	Pawn(char type, std::string _currPlace);
	virtual ~Pawn();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board, bool dontRecurse = false) const override;
	
private:
	bool _isFirstMove;
};
