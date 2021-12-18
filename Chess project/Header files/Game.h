#pragma once
#include <string>
#include "Board.h"
#define DEFUALT_BOARD "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR"

enum gameStatus { whiteTurn, blackTurn, whiteWin, BlackWin, stalemate };

class Game
{
public:
	Game(const std::string& startingCode = DEFUALT_BOARD);
	~Game();
	gameCodes MakeMove(std::string moveCode);
	bool isEnd() const;
	gameStatus getGameStatus() const;
private:
	Board _gameBoard;
	gameStatus _gameStatus;	
};

