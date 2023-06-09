#pragma once
#include "Piece.h"
#include "gameExceptions.h"
#include "Game.h"

class King: public Piece
{
public:
	King(char type, std::string _currPlace);
	virtual ~King();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board, bool dontRecurse = false) const override;
	static bool isPieceThreatened(char type, const Board& board, std::string kingsPlace="");
	static bool isCheckMate(char type, const Board& board, Game* game = nullptr);
	static std::string findPiecePlace(char type, const Board& board);
	virtual bool canAvoidCheck(const Board& board) const override;
};
