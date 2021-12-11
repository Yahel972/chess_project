#pragma once

#include "Piece.h"
#define SIDE_SIZE 8


class Piece;
enum gameCodes;

class Board
{
public:
	Board(const std::string& startingCode);
	~Board();
	gameCodes move(const std::string& moveCode);
	void printBoard() const;
	Piece* operator[](const char pos[2] ) const;
	Piece* &operator[](const char pos[2]);
	Piece* operator() (int x, int y) const;
private:
	Piece* _pieces[SIDE_SIZE][SIDE_SIZE];
};

