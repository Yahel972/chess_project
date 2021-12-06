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
	//gameCodes move(const std::string& moveCode);
	void printBoard() const;
	Piece* operator[](const char pos[2] ) const;
	const Piece* &operator[](const char pos[2]);
private:
	Piece* _pieces[SIDE_SIZE][SIDE_SIZE];
};

