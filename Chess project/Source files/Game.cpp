#include "Game.h"
#include "King.h"
#include <iostream>
#pragma warning(disable:26812)
//recommends to use 'enum class' instead of 'enum'

Game::Game(const std::string& startingCode): _gameBoard(Board(startingCode)), _gameStatus(gameStatus::blackTurn) {}

Game::~Game() {}

gameCodes Game::MakeMove(std::string moveCode)
{
    gameCodes retCode = gameCodes::validMove;
    if (_gameBoard[moveCode.substr(0, 2).data()] && ((isupper(_gameBoard[moveCode.substr(0, 2).data()]->getType()) && _gameStatus == gameStatus::whiteTurn) ||
        (islower(_gameBoard[moveCode.substr(0, 2).data()]->getType()) && _gameStatus == gameStatus::blackTurn)))
    {
        retCode = _gameBoard.move(moveCode);
        if (King::isCheckMate(this->_gameStatus == gameStatus::blackTurn ? 'k' : 'K', this->_gameBoard, this))
        {
            return gameCodes::checkMate;
        }

        if (retCode == gameCodes::validMove || retCode == gameCodes::checkOnEnemy || retCode == gameCodes::checkMate)
        {
            _gameStatus = (gameStatus)!_gameStatus;
        }
    }
    else
    {
        return gameCodes::srcInvalid;
    }
    return retCode;
}

bool Game::isEnd() const
{
    return _gameStatus == gameStatus::BlackWin || _gameStatus == gameStatus::whiteWin;
}

gameStatus Game::getGameStatus() const
{
    return _gameStatus;
}

void Game::setGameStatus(gameStatus newVal)
{
    this->_gameStatus = newVal;
}
