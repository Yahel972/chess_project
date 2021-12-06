#include "Bishop.h"

Bishop::Bishop(char type, std::string _currPlace): Piece(type, _currPlace) {}

Bishop::~Bishop() {}

gameCodes Bishop::checkMove(const std::string& newPlace, const Board& board) const
{
	return gameCodes::validMove;
}
