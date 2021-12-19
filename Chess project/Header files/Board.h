#pragma once

#include "Piece.h"
#define SIDE_SIZE 8


class Piece;
enum gameCodes;

class Board
{
public:
	Board(const std::string& startingCode);
	Board(const Board& other);
	~Board();
	void printBoard() const;
	std::string getBoardAsString() const;
	gameCodes move(const std::string& moveCode, bool dontRecurse = false);
	Piece* operator[](const char pos[2] ) const;
	Piece* &operator[](const char pos[2]);
	Piece* operator() (int x, int y) const;
private:
	Piece* _pieces[SIDE_SIZE][SIDE_SIZE];
};

