#include "Knight.h"

Knight::Knight(char type, std::string _currPlace): Piece(type, _currPlace) {}

Knight::~Knight() {}

gameCodes Knight::checkMove(const std::string& newPlace, const Board& board, bool dontRecurse) const
{
	return gameCodes::checkMate;
}
