#include "Rook.h"

Rook::Rook(char type): Piece(type) {}


Rook::~Rook() {}

gameCodes Rook::checkMove(const std::string& newPlace, const Board& board) const
{
	return gameCodes::validMove;
}
