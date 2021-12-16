#include "pawn.h"

Pawn::Pawn(char type, std::string _currPlace): Piece(type, _currPlace), _isFirstMove(true) {}

Pawn::~Pawn() {}

gameCodes Pawn::checkMove(const std::string& newPlace, const Board& board, bool dontRecurse) const
{
	if (this->_currPlace == newPlace) return gameCodes::invalidSrcIsDst;  // checking if the new place is same as the current place

	if (!Piece::isIndexValid(newPlace)) return gameCodes::invalidIndex;  // checking if the index given is valid

	char currentXIndex = this->_currPlace[0];
	char currentYIndex = this->_currPlace[1];
	char newXIndex = newPlace[0];
	char newYIndex = newPlace[1];

	const char* newPlaceArr = newPlace.data();

	bool isValidMove = false;

	if (isupper(this->getType()))  // white pawn
	{
		isValidMove =
			(int(currentXIndex) == int(newXIndex) && int(currentYIndex) == int(newYIndex) + 2) && (this->_isFirstMove) && (!board[newPlaceArr]) ||  // if it is the first turn the pawn can move double spots!
			(int(currentXIndex) == int(newXIndex) && int(currentYIndex) == int(newYIndex) + 1) && (!board[newPlaceArr]) ||
			(int(currentXIndex) == int(newXIndex) + 1 && int(currentYIndex) == int(newYIndex) + 1) && islower(board[newPlaceArr]->getType()) ||  // eats an enemy troop
			(int(currentXIndex) == int(newXIndex) - 1 && int(currentYIndex) == int(newYIndex) + 1) && islower(board[newPlaceArr]->getType());  // eats an enemy troop
	}
	else  // black pawn
	{
		isValidMove =
			(int(currentXIndex) == int(newXIndex) && int(currentYIndex) == int(newYIndex) - 2) && (this->_isFirstMove) && (!board[newPlaceArr]) ||  // if it is the first turn the pawn can move double spots!
			(int(currentXIndex) == int(newXIndex) && int(currentYIndex) == int(newYIndex) - 1) && (!board[newPlaceArr]) ||
			(int(currentXIndex) == int(newXIndex) + 1 && int(currentYIndex) == int(newYIndex) - 1) && isupper(board[newPlaceArr]->getType()) ||  // eats an enemy troop
			(int(currentXIndex) == int(newXIndex) - 1 && int(currentYIndex) == int(newYIndex) - 1) && isupper(board[newPlaceArr]->getType());  // eats an enemy troop
	}

	// checking if the move is valid:
	if (isValidMove)
	{
		// checking if the pawn is stepping on a place that there is already a piece in his team:
		if (board[newPlaceArr] && ((isupper(board[newPlaceArr]->getType()) && isupper(this->_type)) || (islower(board[newPlaceArr]->getType()) && islower(this->_type))))
			return gameCodes::dstInvalid;

		if (dontRecurse)
		{
			const_cast<Pawn*>(this)->_isFirstMove = false;  // making it available for changes
			return gameCodes::validMove;
		}
		//checking if move causes self king to be threatened
		if ((King::isKingThreatened(isupper(this->_type) ? 'K' : 'k', board)))
			return gameCodes::invalidCheckOnSelf;

		if (King::isCheckMate(this->_type))
		{
			return gameCodes::checkMate;
		}
		//checking if the move caused a check on the other king and NOT checkMate: just a check
		if ((King::isKingThreatened(isupper(this->_type) ? 'k' : 'K', board)) && !King::isCheckMate(this->_type))
			const_cast<Pawn*>(this)->_isFirstMove = false;  // making it available for changes
			return gameCodes::checkOnEnemy;
	}
	else return gameCodes::invalidMove;
	
	const_cast<Pawn*>(this)->_isFirstMove = false;  // making it available for changes
	return gameCodes::validMove;
}
