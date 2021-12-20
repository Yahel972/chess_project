#pragma once
#include <string>
#include "Board.h"
#define DEFUALT_BOARD "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR"

enum gameStatus { whiteTurn, blackTurn, whiteWin, BlackWin, stalemate };

class Game
{
public:
	Game();
	Game(const std::string& startingCode = DEFUALT_BOARD);
	~Game();
	gameCodes MakeMove(std::string moveCode);
	bool isEnd() const;
	gameStatus getGameStatus() const;
	void setGameStatus(gameStatus newVal);
private:
	Board _gameBoard;
	gameStatus _gameStatus;	
};

