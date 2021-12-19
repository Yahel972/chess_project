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
			(int(currentXIndex) == int(newXIndex) + 1 && int(currentYIndex) == int(newYIndex) + 1) && board[newPlaceArr] && islower(board[newPlaceArr]->getType()) ||  // eats an enemy troop
			(int(currentXIndex) == int(newXIndex) - 1 && int(currentYIndex) == int(newYIndex) + 1) && board[newPlaceArr] && islower(board[newPlaceArr]->getType());  // eats an enemy troop
	}
	else  // black pawn
	{
		isValidMove =
			(int(currentXIndex) == int(newXIndex) && int(currentYIndex) == int(newYIndex) - 2) && (this->_isFirstMove) && (!board[newPlaceArr]) ||  // if it is the first turn the pawn can move double spots!
			(int(currentXIndex) == int(newXIndex) && int(currentYIndex) == int(newYIndex) - 1) && (!board[newPlaceArr]) ||
			(int(currentXIndex) == int(newXIndex) + 1 && int(currentYIndex) == int(newYIndex) - 1) && board[newPlaceArr] && isupper(board[newPlaceArr]->getType()) ||  // eats an enemy troop
			(int(currentXIndex) == int(newXIndex) - 1 && int(currentYIndex) == int(newYIndex) - 1) && board[newPlaceArr] && isupper(board[newPlaceArr]->getType());  // eats an enemy troop
	}

	// checking if the move is valid:
	if (isValidMove)
	{
		// checking if the pawn is stepping on a place that there is already a piece in his team:
		if (board[newPlaceArr] && ((isupper(board[newPlaceArr]->getType()) && isupper(this->_type)) || (islower(board[newPlaceArr]->getType()) && islower(this->_type))))
			return gameCodes::dstInvalid;

		if (dontRecurse)
		{
			const_cast<Pawn*>(this)->_isFirstMove = false;  // making it available for changes and updating the first move flag
			return gameCodes::validMove;
		}

		std::string brdAsStr = board.getBoardAsString();
		Board tempBoard(brdAsStr);
		tempBoard.move(std::string(this->_currPlace + newPlace), true);
		//checking if move causes self king to be threatened
		if (King::isPieceThreatened(isupper(this->_type) ? 'K' : 'k', tempBoard))
		{
			return gameCodes::invalidCheckOnSelf;
		}
		//checking if the move caused a check on the other king
		if (King::isPieceThreatened(isupper(this->_type) ? 'k' : 'K', tempBoard))
		{
			//if king is threatened, checking if its a checkmate
			if (King::isCheckMate(isupper(this->_type) ? 'k' : 'K', tempBoard))
			{
				return gameCodes::checkMate;
			}
			//else its just a check
			else
			{
				const_cast<Pawn*>(this)->_isFirstMove = false;  // making it available for changes and updating the first move flag
				return gameCodes::checkOnEnemy;
			}
		}
	}
	else return gameCodes::invalidMove;  // invalid move
	
	const_cast<Pawn*>(this)->_isFirstMove = false;  // making it available for changes and updating the first move flag
	return gameCodes::validMove;
}
