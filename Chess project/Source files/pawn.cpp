#include "pawn.h"

Pawn::Pawn(char type, std::string _currPlace): Piece(type, _currPlace) {}

Pawn::~Pawn() {}

gameCodes Pawn::checkMove(const std::string& newPlace, const Board& board, bool dontRecurse) const
{
	return gameCodes::checkMate;
}
