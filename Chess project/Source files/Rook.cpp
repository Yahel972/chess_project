#include "Rook.h"
#include "King.h"
#include <iostream>
//C'tor
Rook::Rook(char type, std::string _currPlace): Piece(type, _currPlace) {}
//D'tor
Rook::~Rook() {}
//checking if the move is valid or not
gameCodes Rook::checkMove(const std::string& newPlace, const Board& board, bool dontRecurse) const
{
	//checking if the dst index is valid
	if (Piece::isIndexValid(newPlace))
	{
		// checking if the dst index is the current location of the piece
		if (this->_currPlace == newPlace)
		{
			return gameCodes::invalidSrcIsDst;
		}
		//checking if the move is valid in terms of chess rules
		if (newPlace[0] != _currPlace[0] && newPlace[1] != _currPlace[1])
		{
			return gameCodes::invalidMove;
		}
		//checking if the piece has already ate an enemy piece, because his turn ends there
		bool hasAte = false;
		Piece* curr = nullptr;
		//if the player is moving vertically, preform actions on the numbers column(1-8)
		int index = 0;
		char charToInt = 'a';
		if (newPlace[0] == _currPlace[0])
		{
			//if the player is moving horizontally, preform actions on the letters row(a-h)
			index = 1;
			//conversion between char number to int
			charToInt = '0';
		}
		//checking if piece is moving backwards or forwards
		bool goForward = newPlace[index] > _currPlace[index];
		//iterating over all the squarse the piece is moving through
		for (int i = _currPlace[index] - charToInt; i != (newPlace[index] + (goForward ? 1 : -1)) - charToInt; goForward ? i++ : i--)
		{
			//getting the index of the current piece to check
			std::string pieceIndex = std::string(newPlace.substr(!index, 1) + (char)(i + charToInt));
			/*if the move is horizontal, swap between the index letters
			(because it comes as <number><letter> instead of <letter><number> when horizontal way is used)*/
			if (!index)
			{
				std::swap(pieceIndex[0], pieceIndex[1]);
			}
			//getting the current piece from the board
			curr = board[pieceIndex.data()];
			//checking that we dont get source piece as current moving piece
			if (curr != this)
			{
				//check if the piece is trying to eat one of its allies, and if it is, retun the dstInvalid code
				if (curr && isupper(curr->getType()) == isupper(this->_type) || hasAte)
				{
					return gameCodes::dstInvalid;
				}
				//checking if the piece is eating one of the enemy pieces
				if (curr && isupper(curr->getType()) != isupper(this->_type))
				{
					hasAte = true;
				}
			}
		}
		if (dontRecurse)
		{
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
				return gameCodes::checkOnEnemy;
			}
		}
	}
	else
	{
		return gameCodes::invalidIndex;
	}
	return gameCodes::validMove;
}

// function checks if a rook can avoid a chess to happen
bool Rook::canAvoidCheck(const Board& board) const
{
	std::string rightMoves[8] = {};
	std::string leftMoves[8] = {};
	std::string upMoves[8] = {};
	std::string downMoves[8] = {};

	for (int i = 0; i < 8; i++)
	{
		rightMoves[i] += char(this->getCurrPlace()[0] + 1);
		rightMoves[i] += char(this->getCurrPlace()[1]);

		leftMoves[i] += char(this->getCurrPlace()[0] - 1);
		leftMoves[i] += char(this->getCurrPlace()[1]);

		upMoves[i] += char(this->getCurrPlace()[0]);
		upMoves[i] += char(this->getCurrPlace()[1] + 1);

		downMoves[i] += char(this->getCurrPlace()[0]);
		downMoves[i] += char(this->getCurrPlace()[1] - 1);
	}

	for (int i = 0; i < 8; i++)  // checking each move 
	{
		if (this->checkMove(rightMoves[i], board) == gameCodes::validMove) return true;
		if (this->checkMove(leftMoves[i], board) == gameCodes::validMove) return true;
		if (this->checkMove(upMoves[i], board) == gameCodes::validMove) return true;
		if (this->checkMove(downMoves[i], board) == gameCodes::validMove) return true;
	}
	
	return false;
}
