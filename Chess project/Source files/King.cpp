#include "King.h"

King::King(char type, std::string _currPlace) : Piece(type, _currPlace) {}

King::~King() {}

// function checks if a move is valid
gameCodes King::checkMove(const std::string& newPlace, const Board& board) const
{
	if (this->_currPlace == newPlace) return gameCodes::invalidSrcIsDst;  // checking if the new place is same as the current place

	if (!Piece::isIndexValid(newPlace)) return gameCodes::invalidIndex;  // checking if the index given is valid

	char currentXIndex = this->_currPlace[0];
	char currentYIndex = this->_currPlace[1];
	char newXIndex = newPlace[0];
	char newYIndex = newPlace[1];

	const char* newPlaceArr = newPlace.data();

	// checking if the move is valid:
	if ((int(currentXIndex) == int(newXIndex) && int(currentYIndex) == int(newYIndex) + 1) ||
		(int(currentXIndex) == int(newXIndex) && int(currentYIndex) == int(newYIndex) - 1) ||
		(int(currentYIndex) == int(newYIndex) && int(currentXIndex) == int(newXIndex) + 1) ||
		(int(currentYIndex) == int(newYIndex) && int(currentXIndex) == int(newXIndex) - 1) ||
		(int(currentXIndex) == int(newXIndex) - 1 && int(currentYIndex) == int(newYIndex) - 1) ||
		(int(currentXIndex) == int(newXIndex) - 1 && int(currentYIndex) == int(newYIndex) + 1) ||
		(int(currentXIndex) == int(newXIndex) + 1 && int(currentYIndex) == int(newYIndex) - 1) ||
		(int(currentXIndex) == int(newXIndex) + 1 && int(currentYIndex) == int(newYIndex) + 1))
	{
		// checking if the king is stepping on a place that there is already a piece in his team:
		if (board[newPlaceArr] && ((isupper(board[newPlaceArr]->getType()) && isupper(this->_type)) || (islower(board[newPlaceArr]->getType()) && islower(this->_type))))
			return gameCodes::invalidMove;

		// checking if the king ate the other king - victory!!!
		else if (board[newPlaceArr] && tolower(board[newPlaceArr]->getType()) == 'k')
			return gameCodes::checkMate;

		//checking if move causes self king to be threatened
		if ((King::isKingThreatened(this->_type, board)))
			return gameCodes::invalidCheckOnSelf;

		if (King::isCheckMate(this->_type))
		{
			return gameCodes::checkMate;
		}
		//checking if the move caused a check on the other king and NOT checkMate: just a check
		if ((King::isKingThreatened(this->_type == 'K' ? 'k' : 'K', board)) && !King::isCheckMate(this->_type))
			return gameCodes::checkOnEnemy;
	}
	else return gameCodes::invalidMove;

	return gameCodes::validMove;
}

bool King::isKingThreatened(char type /* k to check for black king, K for the white */, const Board& board)
{
	std::string whiteKingPlace = King::findKingsPlace('K', board);
	std::string blackKingPlace = King::findKingsPlace('k', board);
	if (board[(type == 'K' ? blackKingPlace : whiteKingPlace).data()]->checkMove(type == 'k' ? blackKingPlace : whiteKingPlace, board) == gameCodes::validMove)
	{
		return true;  // if the troop has access to the white king's place - it means he is threatened!
	}

	return false;  // invalid input, nothing special
}

bool King::isCheckMate(char type /* k to check for black king, K for the white */)
{
	//TODO(optinal): check if the king cant move anywhere. return true if the king is threatened, else return false.
	//implementation suggestion: change the king location to any valid location,
	//and call isKingThreatened() every time to check if there is any move possible.
	return false;
}

std::string King::findKingsPlace(char type, const Board& board)
{
	if (type == 'k' || type == 'K')  // finding black king
	{
		for (int i = 0, j = 0; i < SIDE_SIZE; i++)
		{
			for (int j = 0; j < SIDE_SIZE; j++)
			{
				if (board(i, j) && board(i, j)->getType() == type)  // if we have found the black king - returning it's place
				{
					return board(i, j)->getCurrPlace();
				}
			}
		}
	}
	else
	{
		throw TypeException("Type given isn't a king!");
	}
	//in case king wasn't found
	return std::string("a1");
}
