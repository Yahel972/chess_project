#include "Knight.h"

Knight::Knight(char type): Piece(type) {}

Knight::~Knight() {}

gameCodes Knight::checkMove(const std::string& newPlace, const Board& board) const
{
	return gameCodes::validMove;
}
