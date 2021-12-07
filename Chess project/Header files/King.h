#pragma once
#include "Piece.h"

class King: public Piece
{
public:
	King(char type, std::string _currPlace);
	virtual ~King();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board) const;
	static bool isKingThreatened(char type);
	static bool isCheckMate(char type);
};
