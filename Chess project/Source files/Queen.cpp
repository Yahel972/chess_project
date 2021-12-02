#include "Queen.h"

Queen::Queen(char type): Piece(type) {}

Queen::~Queen() {}

gameCodes Queen::checkMove(const std::string& newPlace, const Board& board) const
{
	return gameCodes::validMove;
}
