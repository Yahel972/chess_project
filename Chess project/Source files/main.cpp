//temp main for testing
#include <iostream>
#include "Board.h"
#include "gameExceptions.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"
#include "Game.h"
#include <conio.h>

int main()
{
	//conroling a piece in the board
	try 
	{
		Board board(DEFUALT_BOARD);
		board.printBoard();
		std::string curLoc = "", temp = "";
		std::cout << "enter piece index to control:" << std::endl;
		std::cin >> curLoc;
		//use arrows to move piece
		while (true)
		{
			std::system("cls");
			board.printBoard();
			(void)_getch();
			switch (_getch()) 
			{ 
			case 72:
				temp = curLoc;
				temp[1] += 1;
				if (board.move(curLoc + temp) == gameCodes::invalidMove)
				{
					throw IndexException("Can't move an empty spot!");
				}
				curLoc = temp;
				break;
			case 80:
				temp = curLoc;
				temp[1] -= 1;
				if (board.move(curLoc + temp) == gameCodes::invalidMove)
				{
					throw IndexException("Can't move an empty spot!");
				}				curLoc = temp;
				break;
			case 77:
				temp = curLoc;
				temp[0] += 1;
				if (board.move(curLoc + temp) == gameCodes::invalidMove)
				{
					throw IndexException("Can't move an empty spot!");
				}				curLoc = temp;
				break;
			case 75:
				temp = curLoc;
				temp[0] -= 1;
				if (board.move(curLoc + temp) == gameCodes::invalidMove)
				{
					throw IndexException("Can't move an empty spot!");
				}				curLoc = temp;
				break;
			default:
				std::cout << "witch piece to switch to?" << std::endl;
				std::cin >> curLoc;
			}
		}
	}
	catch (const MoveException& moveExc)
	{
		std::cout << std::string(moveExc.what() + std::to_string(moveExc.getErrorCode()) + " (" +  moveExc.getErrorMessage()  + ")") << std::endl;

	}
	catch (const GameException& e)
	{
		std::cout << "GameException has occurred: " << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Uknown exception: " << e.what() << std::endl;
	}
	return 0;
}
