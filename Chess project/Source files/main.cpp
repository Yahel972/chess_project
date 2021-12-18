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
#include <windows.h>

void showCursor();
void hideCursor();

int main()
{
	//conroling a piece in the board
	try 
	{
		Board board(DEFUALT_BOARD);
		hideCursor();
		board.printBoard();
		std::string curLoc = "", temp = "";
		std::cout << "enter piece index to control:" << std::endl;
		showCursor();
		std::cin >> curLoc;
		std::system("cls");
		hideCursor();
		//use arrows to move piece
		while (true)
		{
			std::cout << "\033[H";
			board.printBoard();
			unsigned char ch = _getch();
			if (ch == 224)
			{
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
					std::cout << "which piece to switch to?" << std::endl;
					showCursor();
					std::cin >> curLoc;
					std::system("cls");
					hideCursor();
				}
			}
			else
			{
				switch (ch)
				{
				case 'e':
					temp = curLoc;
					temp[1] += 1;
					temp[0] += 1;
					if (board.move(curLoc + temp) == gameCodes::invalidMove)
					{
						throw IndexException("Can't move an empty spot!");
					}
					curLoc = temp;
					break;
				case 'd':
					temp = curLoc;
					temp[1] -= 1;
					temp[0] += 1;
					if (board.move(curLoc + temp) == gameCodes::invalidMove)
					{
						throw IndexException("Can't move an empty spot!");
					}				curLoc = temp;
					break;
				case 'q':
					temp = curLoc;
					temp[0] -= 1;
					temp[1] += 1;
					if (board.move(curLoc + temp) == gameCodes::invalidMove)
					{
						throw IndexException("Can't move an empty spot!");
					}				curLoc = temp;
					break;
				case 'a':
					temp = curLoc;
					temp[0] -= 1;
					temp[1] -= 1;
					if (board.move(curLoc + temp) == gameCodes::invalidMove)
					{
						throw IndexException("Can't move an empty spot!");
					}				curLoc = temp;
					break;
				}
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

void showCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 10;
	info.bVisible = true;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 10;
	info.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &info);
}