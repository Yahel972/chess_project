#include "Board.h"
#include "gameExceptions.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"
#include <iostream>
#include <cctype>
//Board constructor, initiates the board with pieces
Board::Board(const std::string& startingCode): _pieces()
{
	char str[2] = { 0 };
	for (size_t i = 0, j = 0; i < SIDE_SIZE; i++)
	{
		for (size_t j = 0; j < SIDE_SIZE; j++)
		{
			str[0] = i + 1; 
			str[1] = j + 'a';
			switch (tolower(startingCode[i * SIDE_SIZE + j]))
			{
			case 'q':
;				this->_pieces[i][j] = new Queen(startingCode[i  * SIDE_SIZE + j], std::string(str));
				break;
			case 'k':
				this->_pieces[i][j] = new King(startingCode[i  * SIDE_SIZE + j], std::string(str));
				break;
			case 'r':
				this->_pieces[i][j] = new Rook(startingCode[i  * SIDE_SIZE + j], std::string(str));
				break;
			case 'p':
				this->_pieces[i][j] = new Pawn(startingCode[i  * SIDE_SIZE + j], std::string(str));
				break;
			case 'n':
				this->_pieces[i][j] = new Knight(startingCode[i  * SIDE_SIZE + j], std::string(str));
				break;
			case 'b':
				this->_pieces[i][j] = new Bishop(startingCode[i  * SIDE_SIZE + j], std::string(str));
				break;
			case '#':
				this->_pieces[i][j] = nullptr;
				break;
			default:
				throw TypeException("Invalid piece type!");
				break;
			}
		}
	}
}
//D'tor, deallocates the memory crated for the pieces.
Board::~Board()
{
	for (size_t i = 0, j = 0; i < SIDE_SIZE; i++)
	{
		for (size_t j = 0; j < SIDE_SIZE; j++)
		{
			if (this->_pieces[i][j])
			{
				delete this->_pieces[i][j];
			}
		}
	}
}
//moving a piece in the board
gameCodes Board::move(const std::string& moveCode)
{
	gameCodes retCode = (*(this->_pieces[moveCode[1] - '0' - 1][moveCode[0] - 'a'])).checkMove(moveCode.substr(2, 4), *this);
	if (retCode == gameCodes::validMove || retCode == gameCodes::checkOnEnemy || retCode == gameCodes::checkMate)
	{
		Piece* temp = this->_pieces[moveCode[1] - '0' - 1][moveCode[0] - 'a'];
		std::string tempCurrPlace = this->_pieces[moveCode[1] - '0' - 1][moveCode[0] - 'a']->getCurrPlace();
		this->_pieces[moveCode[1] - '0' - 1][moveCode[0] - 'a']->setCurrPlace(this->_pieces[moveCode[3] - '0' - 1][moveCode[2] - 'a']->getCurrPlace());
		this->_pieces[moveCode[3] - '0' - 1][moveCode[2] - 'a']->setCurrPlace(tempCurrPlace);
		this->_pieces[moveCode[1] - '0' - 1][moveCode[0] - 'a'] = this->_pieces[moveCode[3] - '0' - 1][moveCode[2] - 'a'];
		this->_pieces[moveCode[3] - '0' - 1][moveCode[2] - 'a'] = temp;
	}
	else
	{
		throw MoveException("Invalid move! error code: ", retCode);
	}
	return retCode;
}

void Board::printBoard() const
{
	for (int i = SIDE_SIZE - 1, j = 0; i >= 0; i--)
	{
		std::cout << i + 1 << " ";
		for (size_t j = 0; j < SIDE_SIZE; j++)
		{
			std::cout << (this->_pieces[i][j] ? this->_pieces[i][j]->getType() : '#') << " ";
		}
		std::cout << std::endl;

	}
	std::cout << "  a b c d e f g h" << std::endl;
}

Piece* Board::operator[](const char pos[2]) const
{
	return this->_pieces[pos[1] - '0' - 1][pos[0] - 'a'];
}

const Piece*& Board::operator[](const char pos[2])
{
	return this->_pieces[pos[1] - '0' - 1][pos[0] - 'a'];
}
