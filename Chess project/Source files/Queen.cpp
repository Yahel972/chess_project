#include "Queen.h"

Queen::Queen(char type, std::string _currPlace): Piece(type, _currPlace), Rook(type, _currPlace), Bishop(type, _currPlace) {}

Queen::~Queen() {}

gameCodes Queen::checkMove(const std::string& newPlace, const Board& board, bool dontRecurse) const
{
	//checking if move is linear, and if it is, treating it as a move of a Rook
	if (newPlace[0] == _currPlace[0] || newPlace[1] == _currPlace[1])
	{
		return Rook::checkMove(newPlace, board, dontRecurse);
	}
	//else treating it as move of a Bishop 
	return Bishop::checkMove(newPlace, board, dontRecurse);
}
