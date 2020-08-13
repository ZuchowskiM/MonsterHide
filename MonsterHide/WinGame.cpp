#include "WinGame.h"
#include<iostream>

using std::cout;

WinGame::WinGame(): Game()
{
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
}

WinGame::~WinGame()
{
	//EMPTY
}

bool WinGame::show()
{
	
	Analize();
	

	if (gameEnd)
	{
		SetConsoleTextAttribute(hout, FOREGROUND_RED);
		cout << "GAME OVER" << std::endl;
		SetConsoleTextAttribute(hout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		return true;
	}
	else
	{
		for (int i = 0; i < gridSizeY; i++)
		{
			for (int j = 0; j < gridSizeX; j++)
			{
				if (grid[i][j] == States::Player)
				{
					SetConsoleTextAttribute(hout, FOREGROUND_GREEN);
					cout << "P";
				}
				else if (grid[i][j] == States::Monster)
				{
					SetConsoleTextAttribute(hout, FOREGROUND_RED);
					cout << "M";
				}
				else if (grid[i][j] == States::Diamond)
				{
					SetConsoleTextAttribute(hout, FOREGROUND_BLUE);
					cout << "*";
				}
				else if (grid[i][j] == States::Clear)
				{
					cout << " ";
				}
				else if (grid[i][j] == States::Obstacle)
				{
					SetConsoleTextAttribute(hout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
					cout << "#";
				}
				else if (grid[i][j] == States::Watched)
				{
					SetConsoleTextAttribute(hout, FOREGROUND_GREEN | FOREGROUND_RED);
					cout << "!";
				}
			}
			cout << std::endl;

		}
		SetConsoleTextAttribute(hout, FOREGROUND_BLUE);
		cout << "DIAMONDS COUNT: " << diamondsCount << std::endl;
		//cout << "player posY: " << player.posY << std::endl;
		//cout << "player posX: " << player.posX << std::endl; //zmienic potem na private!!!
		return false;
	}

	
}
