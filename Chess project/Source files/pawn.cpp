#include "pawn.h"

Pawn::Pawn(char type, std::string _currPlace): Piece(type) {}

Pawn::~Pawn() {}

gameCodes Pawn::checkMove(const std::string& newPlace, const Board& board) const
{
	return gameCodes::validMove;
}
