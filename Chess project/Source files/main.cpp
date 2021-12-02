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

int main()
{
	try
	{
		Board board(DEFUALT_BOARD);
		board.printBoard();
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
