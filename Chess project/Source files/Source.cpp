/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Game.h"
#include "gameExceptions.h"
using std::cout;
using std::endl;
using std::string;


int main()
{
	std::system("taskkill /F /IM chessGraphics.exe > nul 2>&1 & start \" \" ..\\chessGraphics.exe");
	Sleep(1000);
	srand(time_t(NULL));

	Pipe p;
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return 0;
		}
	}


	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	strcpy_s(msgToGraphics, DEFUALT_BOARD"0"); // just example...
	/*
	rnbkqbnr
	pppppppp
	########
	########
	########
	########
	PPPPPPPP
	RNBQKBNR
	*/
	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();
	Game game;
	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		// YOUR CODE

	try
	{
		msgToGraphics[0] = (char)(game.MakeMove(msgFromGraphics) + '0');

		// checking victory:
		if (game.getGameStatus() == gameStatus::BlackWin)
		{
			std::cout << "\n\nBlack Player won the match!!!";
			p.close();
			return 0;
		}
		else if (game.getGameStatus() == gameStatus::whiteWin)
		{
			std::cout << "\n\nWhite Player won the match!!!";
			p.close();
			return 0;
		}
	}
	catch (const MoveException& moveExc)
	{
		std::cout << std::string(moveExc.what() + std::to_string(moveExc.getErrorCode()) + " (" + moveExc.getErrorMessage() + ")") << std::endl;

	}
	catch (const GameException& e)
	{
		std::cout << "GameException has occurred: " << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Uknown exception: " << e.what() << std::endl;
	}
		msgToGraphics[1] = 0;

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}
		
	p.close();
	return 0;
}
