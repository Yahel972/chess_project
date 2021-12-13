#pragma once
#include <string>
#include "Board.h"
#define DEFUALT_BOARD "rnbkqbnrpppppppp################################PPPPPPPPRNBQKBNR"

enum gameStatus { whiteTurn, blackTurn, whiteWin, BlackWin, stalemate };

class Game
{
public:
	Game(const std::string& startingCode = DEFUALT_BOARD);
	~Game();
	bool isEnd() const;
	gameStatus getGameStatus() const;
private:
	Board _gameBoard;
	gameStatus _gameStatus;	
};

