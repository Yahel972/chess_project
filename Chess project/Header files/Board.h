#pragma once
#include "Piece.h"
#define SIDE_SIZE 8

class Piece;

class Board
{
public:
	Board(const std::string& startingCode);
	~Board();
private:
	Piece* _pieces[SIDE_SIZE][SIDE_SIZE];
};

