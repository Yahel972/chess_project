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

bool King::isCheckMate(char type, const Board& board)
{
	//Piece* king = board[findPiecePlace(type, board).data()];
	////check if there is more than one threathener
	//if (piecesThreatheningCount == 1)
	//{
	//	//if there isn't:
	//	//check if you can take out or block the threathener
	//	//TODO: check if piece can be blocked
	//	if (isPieceThreatened(' ', board, threathenerLocation) && !isPieceThreatened(type, board))
	//	{
	//		std::cout << threathenerLocation << std::endl;
	//		return false;
	//	}
	//}
	////if there is:
	////check if king can escape
	//int opList[] = {0, 1, -1};
	//bool isTrue = true;
	//for (int i = 0; i < 3; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		if (king->checkMove(std::string(1, king->getCurrPlace()[0] + opList[i]) + 
	//			std::string(1, king->getCurrPlace()[1] + opList[j]), board, true) == gameCodes::validMove
	//			&& !King::isPieceThreatened(' ', board, king->getCurrPlace()))
	//		{
	//			isTrue = false;
	//		}
	//	}

	//return isTrue;
	//}
	return false;
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
