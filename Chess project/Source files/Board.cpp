#include "Board.h"
#include "gameExceptions.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"
#include <cctype>

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

int Board::move(std::string moveCode)
{

}
