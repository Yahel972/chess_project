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
#include <cassert>
//Board constructor, initiates the board with pieces
Board::Board(const std::string& startingCode): _pieces()
{
	char str[3] = { 0 };
	for (size_t i = 0, j = 0; i < SIDE_SIZE; i++)
	{
		for (size_t j = 0; j < SIDE_SIZE; j++)
		{
			str[1] = (int)i + 1 + '0';
			str[0] = (int)j + 'a';
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
// copy constructor
Board::Board(const Board& other)
{
	std::string otherBoardCode = other.getBoardAsString();
	(*this) = Board(otherBoardCode);
}
//D'tor, deallocates the memory crated for the pieces.
Board::~Board()
{
	for (int i = 0, j = 0; i < SIDE_SIZE; i++)
	{
		for (int j = 0; j < SIDE_SIZE; j++)
		{
			if (this->_pieces[i][j])
			{
				delete this->_pieces[i][j];
			}
		}
	}
}
//moving a piece in the board
gameCodes Board::move(const std::string& moveCode, bool dontRecurse)
{
	if ((*this)[moveCode.substr(0, 2).data()])
	{
		gameCodes retCode = dontRecurse ? gameCodes::validMove : (*((*this)[moveCode.substr(0, 2).data()])).checkMove(moveCode.substr(2, 2), *this);
		if (retCode == gameCodes::validMove || retCode == gameCodes::checkOnEnemy || retCode == gameCodes::checkMate)
		{
			delete (*this)[moveCode.substr(2, 2).data()];
			(*this)[moveCode.substr(2, 2).data()] = (*this)[moveCode.substr(0, 2).data()];
			(*this)[moveCode.substr(2, 2).data()]->setCurrPlace(moveCode.substr(2, 2));
			(*this)[moveCode.substr(0, 2).data()] = nullptr;
		}
		return retCode;
	}
	else
	{
		return gameCodes::srcInvalid;
	}
}
//printing the board as chars
void Board::printBoard() const
{
	for (int i = SIDE_SIZE - 1; i >= 0; i--)
	{
		std::cout << i + 1 << " ";
		for (int j = 0; j < SIDE_SIZE; j++)
		{
			std::cout << (this->_pieces[i][j] ? this->_pieces[i][j]->getType() : '#') << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "  a b c d e f g h" << std::endl;
}


std::string Board::getBoardAsString() const
{
	std::string boardStr;
	for (int i = 0; i != SIDE_SIZE; i++)
	{
		for (int j = 0; j < SIDE_SIZE; j++)
		{
			boardStr +=(this->_pieces[i][j] ? this->_pieces[i][j]->getType() : '#');
		}
	}
	return boardStr;
}
// operator[] for getting the value in an index
// use: boardObject["<a-h><1-8>"] 
// outcome: the value in cell XY
Piece* Board::operator[](const char pos[2]) const
{
	if (!Piece::isIndexValid(std::string(pos)))
	{
		throw IndexException("Invalid index!");
	}
	return this->_pieces[pos[1] - '0' - 1][pos[0] - 'a'];
}
// operator[] for setting the value in an index
// use: boardObject["<a-h><1-8>"] = boardObject["<other index>"]
// outcome: the value in cell XY is set to be the value in the right
// warning! - do not set one value to another without keeping its original value somewhere in the array - casuses memory leak / deletion problems
Piece*& Board::operator[](const char pos[2])
{
	if (!Piece::isIndexValid(std::string(pos)))
	{
		throw IndexException("Invalid index!");
	}
	return this->_pieces[pos[1] - '0' - 1][pos[0] - 'a'];
}

// operator() - that is being used as operator [][] 
Piece* Board::operator()(int x, int y) const
{
	std::string coordinate = "  ";

	coordinate[0] = char(x + 97);  // a-h
	coordinate[1] = char(y + 49);  // 1-8

	return (*this)[coordinate.data()];
}
