#include "King.h"

King::King(char type): Piece(type) {}

King::~King() {}

gameCodes King::checkMove(const std::string& newPlace, const Board& board) const
{
	return gameCodes::validMove;
}
