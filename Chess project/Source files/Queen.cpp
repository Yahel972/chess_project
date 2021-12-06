#include "Queen.h"

Queen::Queen(char type, std::string _currPlace): Piece(type, _currPlace) {}

Queen::~Queen() {}

gameCodes Queen::checkMove(const std::string& newPlace, const Board& board) const
{
	return gameCodes::validMove;
}
