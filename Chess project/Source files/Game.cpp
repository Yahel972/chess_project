#include "Game.h"
#pragma warning(disable:26812) //recommends to use 'enum class' instead of 'enum'
Game::Game(const std::string& startingCode): _gameBoard(Board(DEFUALT_BOARD)), _player1(Player(true)),
_player2(Player(false)), _currentPlayer(_player1), _gameStatus(gameStatus::active) {}

Game::~Game() {}

bool Game::isEnd() const
{
    return false;
}
