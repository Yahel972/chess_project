#include "King.h"
#include <iostream>
int piecesThreatheningCount = 0;
std::string threathenerLocation = " ";

King::King(char type, std::string _currPlace) : Piece(type, _currPlace) {}

King::~King() {}

// function checks if a move is valid
gameCodes King::checkMove(const std::string& newPlace, const Board& board, bool dontRecurse) const
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
			return gameCodes::dstInvalid;

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
	else return gameCodes::invalidMove;

	return gameCodes::validMove;
}

bool King::isPieceThreatened(char type /* k to check for black king, K for the white */, const Board& board, std::string piecePlace)
{
	std::string piecePlace_= piecePlace.length() ? piecePlace : King::findPiecePlace(type, board);
	Piece* temp = nullptr;
	bool pieceIsThreatened = false;
	for (int i = 0, j = 0; i < SIDE_SIZE; i++)
	{
		for (int j = 0; j < SIDE_SIZE; j++)
		{
			temp = board(i, j);
			if (temp && isupper(temp->getType()) != isupper(piecePlace.length() ? board[piecePlace_.data()]->getType() : type) && temp->checkMove(piecePlace_, board, true) == gameCodes::validMove)
			{
				// if the troop has access to the white piece's place - it means he is threatened!
				pieceIsThreatened = true;
				threathenerLocation = temp->getCurrPlace();
				piecesThreatheningCount++;
			}

		}
	}
	return pieceIsThreatened;
}

bool King::isCheckMate(char type /* k to check for black king, K for the white */, const Board& board, Game* game)
{
	if (King::isPieceThreatened(isupper(type) ? 'k' : 'K', board)) // if there is a check
	{
		for (int i = 0; i < SIDE_SIZE; i++)
		{
			for (int j = 0; j < SIDE_SIZE; j++)
			{
				Piece* temp = board(i, j);
				if (temp && isupper(temp->getType()) == isupper(type))  // checking all of the enemy troops
				{
					if (temp->canAvoidCheck(board)) return false;
				}
			}
		}
		game->setGameStatus(isupper(type) ? gameStatus::BlackWin : gameStatus::whiteWin);
		return true;  // no piece can avoid the check -> checkmate!
	}

	return false;  // there is not even a chess
}

std::string King::findPiecePlace(char type, const Board& board)
{
	for (int i = 0, j = 0; i < SIDE_SIZE; i++)
	{
		for (int j = 0; j < SIDE_SIZE; j++)
		{
			if (board(i, j) && board(i, j)->getType() == type) 
			{
				return board(i, j)->getCurrPlace();
			}
		}
	}
	//in case piece wasn't found
	return std::string("a1");
}

// function checks if a king can avoid a chess to happen
bool King::canAvoidCheck(const Board& board) const
{
	std::string newPlaces[8] = {};  // a king has 8 different moving possibilities

	newPlaces[0] += char(this->getCurrPlace()[0] - 1);
	newPlaces[0] += char(this->getCurrPlace()[1] - 1);

	newPlaces[1] += char(this->getCurrPlace()[0] - 1);
	newPlaces[1] += char(this->getCurrPlace()[1] + 1);

	newPlaces[2] += char(this->getCurrPlace()[0] + 1);
	newPlaces[2] += char(this->getCurrPlace()[1] + 1);

	newPlaces[3] += char(this->getCurrPlace()[0] + 1);
	newPlaces[3] += char(this->getCurrPlace()[1] - 1);

	newPlaces[4] += char(this->getCurrPlace()[0] + 1);
	newPlaces[4] += char(this->getCurrPlace()[1]);

	newPlaces[5] += char(this->getCurrPlace()[0] - 1);
	newPlaces[5] += char(this->getCurrPlace()[1]);

	newPlaces[6] += char(this->getCurrPlace()[0]);
	newPlaces[6] += char(this->getCurrPlace()[1] + 1);

	newPlaces[7] += char(this->getCurrPlace()[0]);
	newPlaces[7] += char(this->getCurrPlace()[1] - 1);

	for (int i = 0; i < 8; i++)  // checking each move 
	{
		if (this->checkMove(newPlaces[i], board) == gameCodes::validMove) return true;
	}

	return false;
}
