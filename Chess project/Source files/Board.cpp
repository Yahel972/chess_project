#include "Board.h"
#include "gameExceptions.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"
#include <cctype>
//Board constructor, initiates the board with pieces
Board::Board(const std::string& startingCode)
{
	for (size_t i = 0, j = 0; i < startingCode.length() / SIDE_SIZE; i++)
	{
		for (size_t j = 0; j < startingCode.length() / SIDE_SIZE; j++)
		{
			switch (tolower(startingCode[i]))
			{
			case 'q':
				this->_pieces[i][j] = new Queen(startingCode[i * SIDE_SIZE + j]);
				break;
			case 'k':
				this->_pieces[i][j] = King(startingCode[i]);
				break;
			case 'r':
				this->_pieces[i][j] = Rook(startingCode[i]);
				break;
			case 'p':
				this->_pieces[i][j] = Pawn(startingCode[i]);
				break;
			case 'n':
				this->_pieces[i][j] = Knight(startingCode[i]);
				break;
			case 'b':
				this->_pieces[i][j] = Bishop(startingCode[i]);
				break;
			default:
				this->_pieces[i][j] = nullptr;
				break;
			}
		}
	}
}
//D'tor, deallocates the memory crated for the pieces.
Board::~Board()
{
	for (size_t i = 0; i < SIDE_SIZE * SIDE_SIZE; i++)
	{
		if (this->_pieces[i])
		{
			delete this->_pieces[i];
		}
	}
}
//moving a piece in the board
int Board::move(const std::string& moveCode, Board& board)
{
	gameCodes retCode = (*(this->_pieces[moveCode[0] - ('a' - 1)][moveCode[1] - '0'])).checkMove(moveCode.substr(2, 4), board);
	if (retCode == gameCodes::validMove || retCode == gameCodes::checkOnEnemy || retCode == gameCodes::checkMate)
	{
		Piece* temp = this->_pieces[moveCode[0] - ('a' - 1)][moveCode[1] - '0'];
		this->_pieces[moveCode[0] - ('a' - 1)][moveCode[1] - '0'] = this->_pieces[moveCode[2] - ('a' - 1)][moveCode[4] - '0'];
		this->_pieces[moveCode[2] - ('a' - 1)][moveCode[4] - '0'] = temp;
	}
	else
	{
		throw MoveException("Invalid move! error code: ", retCode);
	}
	return retCode;
}