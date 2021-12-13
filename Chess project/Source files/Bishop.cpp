#include "Bishop.h"

Bishop::Bishop(char type, std::string _currPlace): Piece(type, _currPlace) {}

Bishop::~Bishop() {}

gameCodes Bishop::checkMove(const std::string& newPlace, const Board& board, bool dontRecurse) const
{
	return gameCodes::checkMate;
}
