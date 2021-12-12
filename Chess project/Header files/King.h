#pragma once
#include "Piece.h"
#include "TypeException.h"

#pragma warning(disable: 4996)

class King: public Piece
{
public:
	King(char type, std::string _currPlace);
	virtual ~King();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board) const;
	static bool isKingThreatened(char type, const Board& board);
	static bool isCheckMate(char type);
};
