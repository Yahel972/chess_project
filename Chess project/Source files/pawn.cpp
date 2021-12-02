#include "pawn.h"

Pawn::Pawn(char type): Piece(type) {}

Pawn::~Pawn() {}

gameCodes Pawn::checkMove(const std::string& newPlace, const Board& board) const
{
	return gameCodes::validMove;
}
