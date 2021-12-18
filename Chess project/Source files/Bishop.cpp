#include "Bishop.h"
#include "King.h"

Bishop::Bishop(char type, std::string _currPlace): Piece(type, _currPlace) {}

Bishop::~Bishop() {}

gameCodes Bishop::checkMove(const std::string& newPlace, const Board& board, bool dontRecurse) const
{
	//checking if the dst index is valid
	if (Piece::isIndexValid(newPlace))
	{
		// checking if the dst index is the current location of the piece
		if (this->_currPlace == newPlace)
		{
			return gameCodes::invalidSrcIsDst;
		}
		//checking if the move is diagonal or not
		if (newPlace[0] == _currPlace[0] || newPlace[1] == _currPlace[1])//|| newPlace[0] - _currPlace[0] != newPlace[1] - _currPlace[1])
		{
			return gameCodes::invalidMove;
		}
		//checking if the piece has already ate an enemy piece, because his turn ends there
		bool hasAte = false;
		Piece* curr = nullptr;
		int i = 0;
		for (i = _currPlace[0] - 'a'; i != newPlace[0] - 'a'; newPlace[0] > _currPlace[0] ? i++ : i--);
		{
			for (int j = _currPlace[1] - '0'; j != newPlace[1] - '0'; newPlace[1] > _currPlace[1] ? j++ : j--)
			{
				//getting the current piece from the board
				curr = board(i, j);
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
		}
		if (dontRecurse)
		{
			return gameCodes::validMove;
		}
		std::string brdAsStr = board.getBoardAsString();
		Board tempBoard(brdAsStr);
		tempBoard.move(std::string(this->_currPlace + newPlace), true);
		//checking if move causes self king to be threatened
		if (King::isKingThreatened(isupper(this->_type) ? 'K' : 'k', tempBoard))
		{
			return gameCodes::invalidCheckOnSelf;
		}
		//checking if the move caused a check on the other king
		if (King::isKingThreatened(isupper(this->_type) ? 'k' : 'K', tempBoard))
		{
			//if king is threatened, checking if its a checkmate
			if (King::isCheckMate(isupper(this->_type) ? 'k' : 'K'))
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
