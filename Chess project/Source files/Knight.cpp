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
				return gameCodes::checkOnEnemy;
			}
		}
	}
	else return gameCodes::invalidMove;

	return gameCodes::validMove;
}

// function checks if a knight can avoid a chess to happen
bool Knight::canAvoidCheck(const Board& board) const
{
	std::string newPlaces[8] = {};  // a knight has 8 different moving possibilities

	newPlaces[0] += char(this->getCurrPlace()[0] - 2);
	newPlaces[0] += char(this->getCurrPlace()[1] - 1);

	newPlaces[1] += char(this->getCurrPlace()[0] - 2);
	newPlaces[1] += char(this->getCurrPlace()[1] + 1);

	newPlaces[2] += char(this->getCurrPlace()[0] + 2);
	newPlaces[2] += char(this->getCurrPlace()[1] - 1);

	newPlaces[3] += char(this->getCurrPlace()[0] + 2);
	newPlaces[3] += char(this->getCurrPlace()[1] + 1);

	newPlaces[4] += char(this->getCurrPlace()[0] + 1);
	newPlaces[4] += char(this->getCurrPlace()[1] + 2);

	newPlaces[5] += char(this->getCurrPlace()[0] + 1);
	newPlaces[5] += char(this->getCurrPlace()[1] - 2);

	newPlaces[6] += char(this->getCurrPlace()[0] - 1);
	newPlaces[6] += char(this->getCurrPlace()[1] + 2);

	newPlaces[7] += char(this->getCurrPlace()[0] - 1);
	newPlaces[7] += char(this->getCurrPlace()[1] - 2);

	for (int i = 0; i < 8; i++)  // checking each move 
	{
		if (this->checkMove(newPlaces[i], board) == gameCodes::validMove) return true;
	}

	return false;
}
