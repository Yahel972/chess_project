#pragma once
#include <string>
#include "Board.h"
#include "Player.h"
#define DEFUALT_BOARD "rnbkqbnrpppppppp################################PPPPPPPPRNBQKBNR"

enum gameStatus { active, whiteWin, BlackWin, stalemate };

class Game
{
public:
	Game(const std::string& startingCode = DEFUALT_BOARD);
	~Game();
	bool isEnd() const;
private:
	Board _gameBoard;
	Player _player1;
	Player _player2;
	Player _currentPlayer;
	gameStatus _gameStatus;	
};

