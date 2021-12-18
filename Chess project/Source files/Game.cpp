#include "Game.h"
#pragma warning(disable:26812) //recommends to use 'enum class' instead of 'enum'
Game::Game(const std::string& startingCode): _gameBoard(Board(DEFUALT_BOARD)), _gameStatus(gameStatus::whiteTurn) {}

Game::~Game() {}

gameCodes Game::MakeMove(std::string moveCode)
{
    gameCodes retCode = gameCodes::validMove;
    if (_gameBoard[moveCode.substr(0, 2).data()] && ((_gameBoard[moveCode.substr(0, 2).data()]->getType()) && _gameStatus == gameStatus::whiteTurn ||
        islower(_gameBoard[moveCode.substr(0, 2).data()]->getType()) && _gameStatus == gameStatus::blackTurn))
    {
        retCode = _gameBoard.move(moveCode);
        _gameStatus = (gameStatus)!_gameStatus;
    }
    else
    {
        return gameCodes::srcInvalid;
    }
    return retCode;
}

bool Game::isEnd() const
{
    return _gameStatus == gameStatus::BlackWin || _gameStatus == gameStatus::whiteTurn;
}

gameStatus Game::getGameStatus() const
{
    return _gameStatus;
}
