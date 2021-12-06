#include "Bishop.h"

Bishop::Bishop(char type, std::string currPlaces): Piece(type) {}

Bishop::~Bishop() {}

gameCodes Bishop::checkMove(const std::string& newPlace, const Board& board) const
{
	return gameCodes::validMove;
}
