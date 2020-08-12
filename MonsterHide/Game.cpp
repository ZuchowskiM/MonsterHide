#include "Game.h"
#include<cstdlib>
#include<ctime>

Game::Game()
{
	srand(time(NULL));

	gridSizeX = 60;
	gridSizeY = 60;

	grid = new States*[gridSizeX];

	for (int i = 0; i < gridSizeX; i++)
	{
		grid[i] = new States[gridSizeY];
	}

	for (int i = 0; i < gridSizeX; i++)
	{
		for (int j = 0; j < gridSizeY; j++)
		{
			grid[i][j] = States::Clear;
		}
	}

	grid[2][3] = States::Obstacle;
	grid[3][3] = States::Obstacle;
	grid[4][3] = States::Obstacle;
	grid[5][3] = States::Obstacle;

	grid[54][55] = States::Obstacle;
	grid[55][55] = States::Obstacle;
	grid[56][55] = States::Obstacle;
	grid[57][55] = States::Obstacle;

	for (int i = 0; i < 60; i++)
	{
		grid[i][0] = States::Obstacle;
		grid[i][59] = States::Obstacle;
		grid[0][i] = States::Obstacle;
		grid[59][i] = States::Obstacle;
	}

	player.place(49, 29);
	monster.place(9, 29);

	movesCount = 0;
	diamondsCount = 0;

	monsterTargetPointX = 0;
	monsterTargetPointY = 0;

	//PLACING DIAMOND RANDOMLY
	diamondOnBoard = false;

	while (!diamondOnBoard)
	{
		diamond.posX = rand() % 60;
		diamond.posY = rand() % 60;

		if (grid[diamond.posY][diamond.posX] == States::Clear)
		{
			grid[diamond.posY][diamond.posX] = States::Diamond;
			diamondOnBoard = true;
		}

	}

	//PLACING MONSTER ACTIVE WAYPOINT
	monsterTargetActive = false;

	while (!monsterTargetActive)
	{
		monsterTargetPointX = rand() % 60;
		monsterTargetPointY = rand() % 60;

		if (grid[monsterTargetPointX][monsterTargetPointY] != States::Obstacle)
		{
			monsterTargetActive = true;
		}

	}

}

Game::~Game()
{
	for (int i = 0; i < gridSizeX; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
}

void Game::Analize()
{

	//POSITIONING MOVING OBJECTS
	grid[monster.posY][monster.posX] = States::Monster;
	grid[player.posY][player.posX] = States::Player;
	

	////DRAWING MONSTER VISION #TODO////
	if (monster.direction == Monster::Directions::right)
	{
		if(monster.posX + 1 < 60 && grid[monster.posY][monster.posX + 1] == States::Clear)
			grid[monster.posY][monster.posX + 1] = States::Watched;

		if (monster.posX + 2 < 60 && grid[monster.posY][monster.posX + 2] == States::Clear)
			grid[monster.posY][monster.posX + 2] = States::Watched;

		if (monster.posX + 3 < 60 && grid[monster.posY][monster.posX + 3] == States::Clear)
			grid[monster.posY][monster.posX + 3] = States::Watched;
	}
	else if(monster.direction == Monster::Directions::left)
	{
		if (monster.posX - 1 >= 0 && grid[monster.posY][monster.posX - 1] == States::Clear)
			grid[monster.posY][monster.posX - 1] = States::Watched;

		if (monster.posX - 2 >= 0 && grid[monster.posY][monster.posX - 2] == States::Clear)
			grid[monster.posY][monster.posX - 2] = States::Watched;

		if (monster.posX - 3 >= 0 && grid[monster.posY][monster.posX - 3] == States::Clear)
			grid[monster.posY][monster.posX - 3] = States::Watched;
	}
	else if (monster.direction == Monster::Directions::up)
	{
		if (monster.posY + 1 < 60 && grid[monster.posY + 1][monster.posX] == States::Clear)
			grid[monster.posY + 1][monster.posX] = States::Watched;

		if (monster.posY + 2 < 60 && grid[monster.posY + 2][monster.posX] == States::Clear)
			grid[monster.posY + 2][monster.posX] = States::Watched;

		if (monster.posY + 3 < 60 && grid[monster.posY + 3][monster.posX] == States::Clear)
			grid[monster.posY + 3][monster.posX] = States::Watched;
	}
	else if (monster.direction == Monster::Directions::down)
	{
		if (monster.posY - 1 >= 0 && grid[monster.posY - 1][monster.posX] == States::Clear)
			grid[monster.posY - 1][monster.posX] = States::Watched;

		if (monster.posY - 2 >= 0 && grid[monster.posY - 2][monster.posX] == States::Clear)
			grid[monster.posY - 1][monster.posX] = States::Watched;

		if (monster.posY - 3 >= 0 && grid[monster.posY - 3][monster.posX] == States::Clear)
			grid[monster.posY - 3][monster.posX] = States::Watched;
	}

	//CHECKING IF PLAYER TAKEN DIAMOND
	if (player.posX == diamond.posX && player.posY == diamond.posY)
	{
		diamondsCount++;
		diamondOnBoard = false;
	}

	//PLACING DIAMOND
	while (!diamondOnBoard)
	{
		diamond.posX = rand() % 60;
		diamond.posY = rand() % 60;

		if (grid[diamond.posY][diamond.posX] == States::Clear)
		{
			grid[diamond.posY][diamond.posX] = States::Diamond;
			diamondOnBoard = true;
		}

	}

	//CHECKING IF MONSTER REACHED POINT
	if (monster.posX == monsterTargetPointX && monster.posY == monsterTargetPointY)
	{
		monsterTargetActive = false;
	}

	//PLACING MONSTER ACTIVE WAYPOINT
	while (!monsterTargetActive)
	{
		monsterTargetPointX = rand() % 60;
		monsterTargetPointY = rand() % 60;

		if (grid[monsterTargetPointX][monsterTargetPointY] != States::Obstacle)
		{
			monsterTargetActive = true;
		}

	}


}

void Game::getPlayerMove(int KeyNumber)
{
	
	switch (KeyNumber) 
	{
	case 72:
		if (grid[player.posY - 1][player.posX] != States::Obstacle)
		{
			grid[player.posY][player.posX] = States::Clear;
			player.place(player.posX, player.posY - 1);
		}
		break;
	case 80:
		if (grid[player.posY + 1][player.posX] != States::Obstacle)
		{
			grid[player.posY][player.posX] = States::Clear;
			player.place(player.posX, player.posY + 1);
		}
		break;
	case 75:
		if (grid[player.posY][player.posX - 1] != States::Obstacle)
		{
			grid[player.posY][player.posX] = States::Clear;
			player.place(player.posX - 1, player.posY);
		}
		break;
	case 77:
		if (grid[player.posY][player.posX + 1] != States::Obstacle)
		{
			grid[player.posY][player.posX] = States::Clear;
			player.place(player.posX + 1, player.posY);
		}
		break;
	default:
		break;
	}
	
}

void Game::constructMonsterPath()
{
	bool pointFound = false;
	path.emplace_back(std::make_pair(std::make_pair(monster.posX, monster.posY), std::make_pair(-1, -1)));

	int i = 0;
	while (!pointFound)
	{
		
		path.emplace_back(std::make_pair(std::make_pair(path[i].first.first, path[i].first.second - 1), std::make_pair(path[i].first.first, path[i].first.second)));
		if (path[i].first.first == monsterTargetPointX && path[i].first.second - 1 == monsterTargetPointY)
		{
			pointFound = true;
			break;
		}

		path.emplace_back(std::make_pair(std::make_pair(path[i].first.first + 1, path[i].first.second), std::make_pair(path[i].first.first, path[i].first.second)));
		if (path[i].first.first + 1 == monsterTargetPointX && path[i].first.second == monsterTargetPointY)
		{
			pointFound = true;
			break;
		}

		path.emplace_back(std::make_pair(std::make_pair(path[i].first.first, path[i].first.second + 1), std::make_pair(path[i].first.first, path[i].first.second)));
		if (path[i].first.first == monsterTargetPointX && path[i].first.second + 1 == monsterTargetPointY)
		{
			pointFound = true;
			break;
		}

		path.emplace_back(std::make_pair(std::make_pair(path[i].first.first - 1, path[i].first.second), std::make_pair(path[i].first.first, path[i].first.second)));
		if (path[i].first.first - 1 == monsterTargetPointX && path[i].first.second == monsterTargetPointY)
		{
			pointFound = true;
			break;
		}
		
		i++;
	}


}