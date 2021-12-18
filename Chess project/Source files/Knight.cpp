#include "Knight.h"

Knight::Knight(char type, std::string _currPlace): Piece(type, _currPlace) {}

Knight::~Knight() {}

gameCodes Knight::checkMove(const std::string& newPlace, const Board& board, bool dontRecurse) const
{
	if (this->_currPlace == newPlace) return gameCodes::invalidSrcIsDst;  // checking if the new place is same as the current place

	if (!Piece::isIndexValid(newPlace)) return gameCodes::invalidIndex;  // checking if the index given is valid

	char currentXIndex = this->_currPlace[0];
	char currentYIndex = this->_currPlace[1];
	char newXIndex = newPlace[0];
	char newYIndex = newPlace[1];

	const char* newPlaceArr = newPlace.data();

	// checking if the move is valid:
	if ((int(currentXIndex) == int(newXIndex) + 2 && int(currentYIndex) == int(newYIndex) + 1) ||
		(int(currentXIndex) == int(newXIndex) + 2 && int(currentYIndex) == int(newYIndex) - 1) ||
		(int(currentXIndex) == int(newXIndex) - 2 && int(currentYIndex) == int(newYIndex) + 1) ||
		(int(currentXIndex) == int(newXIndex) - 2 && int(currentYIndex) == int(newYIndex) - 1) ||
		(int(currentXIndex) == int(newXIndex) + 1 && int(currentYIndex) == int(newYIndex) + 2) ||
		(int(currentXIndex) == int(newXIndex) + 1 && int(currentYIndex) == int(newYIndex) - 2) ||
		(int(currentXIndex) == int(newXIndex) - 1 && int(currentYIndex) == int(newYIndex) + 2) ||
		(int(currentXIndex) == int(newXIndex) - 1 && int(currentYIndex) == int(newYIndex) - 2))
	{
		// checking if the knight is stepping on a place that there is already a piece in his team:
		if (board[newPlaceArr] && ((isupper(board[newPlaceArr]->getType()) && isupper(this->_type)) || (islower(board[newPlaceArr]->getType()) && islower(this->_type))))
			return gameCodes::dstInvalid;
		
		if (dontRecurse)
			return gameCodes::validMove;
		
		//checking if move causes self king to be threatened
		if ((King::isKingThreatened(isupper(this->_type) ? 'K' : 'k', board)))
			return gameCodes::invalidCheckOnSelf;

		if (King::isCheckMate(this->_type))
			return gameCodes::checkMate;
		
		//checking if the move caused a check on the other king and NOT checkMate: just a check
		if ((King::isKingThreatened(isupper(this->_type) ? 'K' : 'k', board)) && !King::isCheckMate(this->_type))
			return gameCodes::checkOnEnemy;
	}
	else return gameCodes::invalidMove;

	return gameCodes::validMove;
}
