#pragma once
#include "Piece.h"
#include "gameExceptions.h"

class King: public Piece
{
public:
	King(char type, std::string _currPlace);
	virtual ~King();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board, bool dontRecurse = false) const override;
	static bool isPieceThreatened(char type, const Board& board, std::string kingsPlace="");
	static bool isCheckMate(char type, const Board& board);
	static std::string findPiecePlace(char type, const Board& board);
};
