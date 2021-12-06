#include "King.h"

King::King(char type, std::string _currPlace): Piece(type, _currPlace) {}

King::~King() {}

gameCodes King::checkMove(const std::string& newPlace, const Board& board) const
{
	return gameCodes::validMove;
}
