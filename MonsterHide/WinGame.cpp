#include "WinGame.h"
#include<iostream>

using std::cout;

WinGame::WinGame(): Game()
{
	//EMPTY
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
		cout << "GAME OVER" << std::endl;
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
					cout << "P";
				}
				else if (grid[i][j] == States::Monster)
				{
					cout << "M";
				}
				else if (grid[i][j] == States::Diamond)
				{
					cout << "^";
				}
				else if (grid[i][j] == States::Clear)
				{
					cout << " ";
				}
				else if (grid[i][j] == States::Obstacle)
				{
					cout << "#";
				}
				else if (grid[i][j] == States::Watched)
				{
					cout << "!";
				}
			}
			cout << std::endl;

		}
		cout << "DIAMONDS COUNT: " << diamondsCount << std::endl;
		cout << "player posY: " << player.posY << std::endl;
		cout << "player posX: " << player.posX << std::endl; //zmienic potem na private!!!
		return false;
	}

	
}
