#include "Game.h"
#pragma warning(disable:26812) //recommends to use 'enum class' instead of 'enum'
Game::Game(const std::string& startingCode): _gameBoard(Board(DEFUALT_BOARD)), _gameStatus(gameStatus::whiteWin) {}

Game::~Game() {}

bool Game::isEnd() const
{
    return _gameStatus == gameStatus::BlackWin || _gameStatus == gameStatus::whiteWin;
}

gameStatus Game::getGameStatus() const
{
    return _gameStatus;
}
