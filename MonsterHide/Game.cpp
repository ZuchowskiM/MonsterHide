#include "Game.h"
#include<cstdlib>
#include<ctime>

Game::Game()
{
	
	srand(unsigned int(time(NULL)));

	gridSizeX = 60;
	gridSizeY = 15;

	grid = new States*[gridSizeY];

	for (int i = 0; i < gridSizeY; i++)
	{
		grid[i] = new States[gridSizeX];
	}

	for (int i = 0; i < gridSizeY; i++)
	{
		for (int j = 0; j < gridSizeX; j++)
		{
			grid[i][j] = States::Clear;
		}
	}

	//PLACING OBSTACLES ON MAP
	drawObstacles();

	for (int i = 0; i < gridSizeY; i++)
	{
		grid[i][0] = States::Obstacle;
		grid[i][gridSizeX -1] = States::Obstacle;
		
	}

	for (int i = 0; i < gridSizeX; i++)
	{
		grid[0][i] = States::Obstacle;
		grid[gridSizeY - 1][i] = States::Obstacle;
	}

	player.place(10, 9);
	monster.place(50, 9);

	movesCount = 0;
	diamondsCount = 0;

	monsterTargetPointX = 0;
	monsterTargetPointY = 0;

	//PLACING DIAMOND RANDOMLY
	diamondOnBoard = false;

	while (!diamondOnBoard)
	{
		diamond.posX = rand() % gridSizeX;
		diamond.posY = rand() % gridSizeY;

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
		monsterTargetPointX = rand() % gridSizeX;
		monsterTargetPointY = rand() % gridSizeY;

		if (grid[monsterTargetPointY][monsterTargetPointX] != States::Obstacle)
		{
			monsterTargetActive = true;
		}

	}

	constructMonsterPath();
	monsterPathCurrentStep = 0;

	gameEnd = false;

}

Game::~Game()
{
	for (int i = 0; i < gridSizeY; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
}

void Game::Analize()
{
	//CHEKING IF PLAYER IS ON VISION
	if (grid[player.posY][player.posX] == States::Watched)
	{
		gameEnd = true;
		return;
	}

	//POSITIONING MOVING OBJECTS
	grid[diamond.posY][diamond.posX] = States::Diamond;
	grid[monster.posY][monster.posX] = States::Monster;
	grid[player.posY][player.posX] = States::Player;
	

	
	//CHECKING IF PLAYER TAKEN DIAMOND
	if (player.posX == diamond.posX && player.posY == diamond.posY)
	{
		diamondsCount++;
		diamondOnBoard = false;
	}


	//PLACING DIAMOND
	while (!diamondOnBoard)
	{
		diamond.posX = rand() % gridSizeX;
		diamond.posY = rand() % gridSizeY;

		if (grid[diamond.posY][diamond.posX] == States::Clear)
		{
			grid[diamond.posY][diamond.posX] = States::Diamond;
			diamondOnBoard = true;
		}

	}

	//CHECKING IF MONSTER REACHED POINT
	if (monsterPathCurrentStep == path.size() - 1)
	{
		monsterTargetActive = false;
	}

	//PLACING MONSTER ACTIVE WAYPOINT
	while (!monsterTargetActive)
	{
		monsterTargetPointX = rand() % gridSizeX;
		monsterTargetPointY = rand() % gridSizeY;

		if (grid[monsterTargetPointY][monsterTargetPointX] != States::Obstacle)
		{
			monsterTargetActive = true;
			constructMonsterPath();
			monsterPathCurrentStep = 0;
		}

	}
	//MONSTER MAKING MOVE
	monsterPathCurrentStep++;
	grid[monster.posY][monster.posX] = States::Clear;
	monster.makeStep(path[monsterPathCurrentStep].first, path[monsterPathCurrentStep].second);
	grid[monster.posY][monster.posX] = States::Monster;

	////DRAWING MONSTER VISION////
	drawMonsterVison();
	
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
	path.clear();
	path.emplace_back(monster.posX, monster.posY);

	bool pointFound = false;
	int currentcost = INT_MAX;
	int cost1 = 0,cost2 = 0,cost3 = 0,cost4 = 0;
	int previousNode = 0;

	/*bool** nodes = new bool* [gridSizeY];

	for (int i = 0; i < gridSizeY; i++)
	{
		nodes[i] = new bool[gridSizeX];
	}

	for (int i = 0; i < gridSizeY; i++)
	{
		for (int j = 0; j < gridSizeX; j++)
		{
			nodes[i][j] = false;
		}
	}
	
	nodes[monster.posY][monster.posX] = true;*/

	while (!pointFound)
	{
		cost1 = 0; cost2 = 0; cost3 = 0; cost4 = 0;
		currentcost = INT_MAX;
		
		if (grid[path.back().second - 1][path.back().first] != States::Obstacle && previousNode != 1)
			cost1 = std::abs(monsterTargetPointX - path.back().first) + std::abs(monsterTargetPointY - (path.back().second - 1));
		else
			cost1 = INT_MAX;

		if (grid[path.back().second][path.back().first + 1] != States::Obstacle && previousNode != 2)
			cost2 = std::abs(monsterTargetPointX - (path.back().first + 1)) + std::abs(monsterTargetPointY - (path.back().second));
		else
			cost2 = INT_MAX;

		if (grid[path.back().second + 1][path.back().first] != States::Obstacle && previousNode != 3)
			cost3 = std::abs(monsterTargetPointX - path.back().first) + std::abs(monsterTargetPointY - (path.back().second + 1));
		else
			cost3 = INT_MAX;

		if (grid[path.back().second][path.back().first - 1] != States::Obstacle && previousNode != 4)
			cost4 = std::abs(monsterTargetPointX - (path.back().first - 1)) + std::abs(monsterTargetPointY - (path.back().second));
		else
			cost4 = INT_MAX;

		currentcost = std::min({ cost1, cost2, cost3, cost4 });


		if (currentcost == cost1 )
		{
			path.emplace_back(path.back().first, path.back().second - 1);
			previousNode = 3;

			if (path.back().first == monsterTargetPointX && path.back().second == monsterTargetPointY)
			{
				break;
			}
		}
		else if (currentcost == cost2 )
		{
			path.emplace_back(path.back().first + 1, path.back().second);
			previousNode = 4;

			if (path.back().first == monsterTargetPointX && path.back().second == monsterTargetPointY)
			{
				break;
			}
		}
		else if (currentcost == cost3 )
		{
			path.emplace_back(path.back().first, path.back().second + 1);
			previousNode = 1;

			if (path.back().first == monsterTargetPointX && path.back().second == monsterTargetPointY)
			{
				break;
			}
		}
		else if (currentcost == cost4 )
		{
			path.emplace_back(path.back().first - 1, path.back().second);
			previousNode = 2;

			if (path.back().first == monsterTargetPointX && path.back().second == monsterTargetPointY)
			{
				break;
			}
		}



		
		
		/*//UP
		cost = std::abs(monsterTargetPointX - path.back().first) + std::abs(monsterTargetPointY - (path.back().second - 1));
		
		if (grid[path.back().second - 1][path.back().first] != States::Obstacle && cost < currentcost)
		{
			currentcost = cost;
			path.emplace_back(path.back().first, path.back().second - 1);
			

			if (path.back().first == monsterTargetPointX && path.back().second == monsterTargetPointY)
			{
				break;
			}
		}

		//RIGHT
		cost = std::abs(monsterTargetPointX - (path.back().first + 1)) + std::abs(monsterTargetPointY - (path.back().second));
		if (grid[path.back().second][path.back().first + 1] != States::Obstacle && cost < currentcost)
		{
			currentcost = cost;

			if(path.size() > 1)
				path.pop_back();

			path.emplace_back(path.back().first + 1, path.back().second);
			

			if (path.back().first == monsterTargetPointX && path.back().second == monsterTargetPointY)
			{
				break;
			}
		}

		//DOWN
		cost = std::abs(monsterTargetPointX - path.back().first) + std::abs(monsterTargetPointY - (path.back().second + 1));
		if (grid[path.back().second + 1][path.back().first] != States::Obstacle && cost < currentcost)
		{
			currentcost = cost;

			if (path.size() > 1)
				path.pop_back();

			path.emplace_back(path.back().first, path.back().second + 1);
			

			if (path.back().first == monsterTargetPointX && path.back().second == monsterTargetPointY)
			{
				break;
			}
		}

		//LEFT
		cost = std::abs(monsterTargetPointX - (path.back().first - 1)) + std::abs(monsterTargetPointY - (path.back().second));
		if (grid[path.back().second][path.back().first - 1] != States::Obstacle && cost < currentcost)
		{
			currentcost = cost;

			if (path.size() > 1)
				path.pop_back();

			path.emplace_back(path.back().first -1, path.back().second);

			if (path.back().first == monsterTargetPointX && path.back().second == monsterTargetPointY)
			{
				break;
			}
		}*/
	}
}

void Game::drawMonsterVison()
{
	for (int i = 0; i < gridSizeY; i++)
	{
		for (int j = 0; j < gridSizeX; j++)
		{
			if (grid[i][j] == States::Watched)
				grid[i][j] = States::Clear;
		}

	}

	if (monster.direction == Monster::Directions::right)
	{
		//STRAIGHT LINE
		if (monster.posX + 1 < gridSizeX && grid[monster.posY][monster.posX + 1] == States::Clear)
		{
			grid[monster.posY][monster.posX + 1] = States::Watched;
			if (monster.posX + 2 < gridSizeX && grid[monster.posY][monster.posX + 2] == States::Clear)
			{
				grid[monster.posY][monster.posX + 2] = States::Watched;
				if (monster.posX + 3 < gridSizeX && grid[monster.posY][monster.posX + 3] == States::Clear)
				{
					grid[monster.posY][monster.posX + 3] = States::Watched;
					if (monster.posX + 4 < gridSizeX && grid[monster.posY][monster.posX + 4] == States::Clear)
					{
						grid[monster.posY][monster.posX + 4] = States::Watched;
					}
						
				}
			}
		}
			
		//UPPER PART
		
		if (monster.posX + 1 < gridSizeX && monster.posY - 1 >= 0 && grid[monster.posY - 1][monster.posX + 1] == States::Clear)
		{
			grid[monster.posY - 1][monster.posX + 1] = States::Watched;
			if (monster.posX + 2 < gridSizeX && monster.posY - 2 >= 0 && grid[monster.posY - 2][monster.posX + 2] == States::Clear)
			{
				grid[monster.posY - 2][monster.posX + 2] = States::Watched;
			}

			if (monster.posX + 2 < gridSizeX && monster.posY - 1 >= 0 && grid[monster.posY - 1][monster.posX + 2] == States::Clear)
			{
				grid[monster.posY - 1][monster.posX + 2] = States::Watched;

				if (monster.posX + 3 < gridSizeX && monster.posY - 1 >= 0 && grid[monster.posY - 1][monster.posX + 3] == States::Clear)
				{
					grid[monster.posY - 1][monster.posX + 3] = States::Watched;
				}

			}
				
		}
			
		//DOWN PART
		if (monster.posX + 1 < gridSizeX && monster.posY + 1 < gridSizeY && grid[monster.posY + 1][monster.posX + 1] == States::Clear)
		{
			grid[monster.posY + 1][monster.posX + 1] = States::Watched;
			if (monster.posX + 2 < gridSizeX && monster.posY + 2 < gridSizeY && grid[monster.posY + 2][monster.posX + 2] == States::Clear)
			{
				grid[monster.posY + 2][monster.posX + 2] = States::Watched;
			}

			if (monster.posX + 2 < gridSizeX && monster.posY + 1 < gridSizeY && grid[monster.posY + 1][monster.posX + 2] == States::Clear)
			{
				grid[monster.posY + 1][monster.posX + 2] = States::Watched;
				if (monster.posX + 3 < gridSizeX && monster.posY + 1 < gridSizeY && grid[monster.posY + 1][monster.posX + 3] == States::Clear)
				{
					grid[monster.posY + 1][monster.posX + 3] = States::Watched;
				}

			}
				
		}
			
	}
	else if (monster.direction == Monster::Directions::left)
	{
		//STRAIGHT LINE
		if (monster.posX - 1 >= 0 && grid[monster.posY][monster.posX - 1] == States::Clear)
		{
			grid[monster.posY][monster.posX - 1] = States::Watched;
			if (monster.posX - 2 >= 0 && grid[monster.posY][monster.posX - 2] == States::Clear)
			{
				grid[monster.posY][monster.posX - 2] = States::Watched;
				if (monster.posX - 3 >= 0 && grid[monster.posY][monster.posX - 3] == States::Clear)
				{
					grid[monster.posY][monster.posX - 3] = States::Watched;
					if (monster.posX - 4 >= 0 && grid[monster.posY][monster.posX - 4] == States::Clear)
						grid[monster.posY][monster.posX - 4] = States::Watched;
				}	
			}
				
		}
			
		//UPPER PART
		if (monster.posX - 1 >= 0 && monster.posY - 1 >= 0 && grid[monster.posY - 1][monster.posX - 1] == States::Clear)
		{
			grid[monster.posY - 1][monster.posX - 1] = States::Watched;
			if (monster.posX - 2 >= 0 && monster.posY - 2 >= 0 && grid[monster.posY - 2][monster.posX - 2] == States::Clear)
				grid[monster.posY - 2][monster.posX - 2] = States::Watched;

			if (monster.posX - 2 >= 0 && monster.posY - 1 >= 0 && grid[monster.posY - 1][monster.posX - 2] == States::Clear)
			{
				grid[monster.posY - 1][monster.posX - 2] = States::Watched;
				if (monster.posX - 3 >= 0 && monster.posY - 1 >= 0 && grid[monster.posY - 1][monster.posX - 3] == States::Clear)
					grid[monster.posY - 1][monster.posX - 3] = States::Watched;
			}
		}
			
		//DOWN PART
		if (monster.posX - 1 >= 0 && monster.posY + 1 < gridSizeY && grid[monster.posY + 1][monster.posX - 1] == States::Clear)
		{
			grid[monster.posY + 1][monster.posX - 1] = States::Watched;
			if (monster.posX - 2 >= 0 && monster.posY + 2 < gridSizeY && grid[monster.posY + 2][monster.posX - 2] == States::Clear)
				grid[monster.posY + 2][monster.posX - 2] = States::Watched;

			if (monster.posX - 2 >= 0 && monster.posY + 1 < gridSizeY && grid[monster.posY + 1][monster.posX - 2] == States::Clear)
			{
				grid[monster.posY + 1][monster.posX - 2] = States::Watched;
				if (monster.posX - 3 >= 0 && monster.posY + 1 < gridSizeY && grid[monster.posY + 1][monster.posX - 3] == States::Clear)
					grid[monster.posY + 1][monster.posX - 3] = States::Watched;
			}

		}
			
	}
	else if (monster.direction == Monster::Directions::up)
	{
		//STRAIGHT LINE
		if (monster.posY - 1 >= 0 && grid[monster.posY - 1][monster.posX] == States::Clear)
		{
			grid[monster.posY - 1][monster.posX] = States::Watched;
			if (monster.posY - 2 >= 0 && grid[monster.posY - 2][monster.posX] == States::Clear)
			{
				grid[monster.posY - 2][monster.posX] = States::Watched;
				if (monster.posY - 3 >= 0 && grid[monster.posY - 3][monster.posX] == States::Clear)
				{
					grid[monster.posY - 3][monster.posX] = States::Watched;
					if (monster.posY - 4 >= 0 && grid[monster.posY - 4][monster.posX] == States::Clear)
						grid[monster.posY - 4][monster.posX] = States::Watched;
				}
			}
				
		}
			

		//RIGHT PART
		if (monster.posY - 1 >= 0 && monster.posX + 1 < gridSizeX && grid[monster.posY - 1][monster.posX + 1] == States::Clear)
		{
			grid[monster.posY - 1][monster.posX + 1] = States::Watched;
			if (monster.posY - 2 >= 0 && monster.posX + 2 < gridSizeX && grid[monster.posY - 2][monster.posX + 2] == States::Clear)
				grid[monster.posY - 2][monster.posX + 2] = States::Watched;

			if (monster.posY - 2 >= 0 && monster.posX + 1 < gridSizeX && grid[monster.posY - 2][monster.posX + 1] == States::Clear)
			{
				grid[monster.posY - 2][monster.posX + 1] = States::Watched;
				if (monster.posY - 3 >= 0 && monster.posX + 1 < gridSizeX && grid[monster.posY - 3][monster.posX + 1] == States::Clear)
					grid[monster.posY - 3][monster.posX + 1] = States::Watched;

			}
				
		}
			
		//LEFT PART
		if (monster.posY - 1 >= 0 && monster.posX - 1 >= 0 && grid[monster.posY - 1][monster.posX - 1] == States::Clear)
		{
			grid[monster.posY - 1][monster.posX - 1] = States::Watched;
			if (monster.posY - 2 >= 0 && monster.posX - 2 >= 0 && grid[monster.posY - 2][monster.posX - 2] == States::Clear)
				grid[monster.posY - 2][monster.posX - 2] = States::Watched;

			if (monster.posY - 2 >= 0 && monster.posX - 1 >= 0 && grid[monster.posY - 2][monster.posX - 1] == States::Clear)
			{
				grid[monster.posY - 2][monster.posX - 1] = States::Watched;
				if (monster.posY - 3 >= 0 && monster.posX - 1 >= 0 && grid[monster.posY - 3][monster.posX - 1] == States::Clear)
					grid[monster.posY - 3][monster.posX - 1] = States::Watched;
			}
				
		}
		
	}
	else if (monster.direction == Monster::Directions::down)
	{
		//STRAIGHT LINE
		if (monster.posY + 1 < gridSizeY && grid[monster.posY + 1][monster.posX] == States::Clear)
		{
			grid[monster.posY + 1][monster.posX] = States::Watched;
			if (monster.posY + 2 < gridSizeY && grid[monster.posY + 2][monster.posX] == States::Clear)
			{
				grid[monster.posY + 2][monster.posX] = States::Watched;
				if (monster.posY + 3 < gridSizeY && grid[monster.posY + 3][monster.posX] == States::Clear)
				{
					grid[monster.posY + 3][monster.posX] = States::Watched;
					if (monster.posY + 4 < gridSizeY && grid[monster.posY + 4][monster.posX] == States::Clear)
						grid[monster.posY + 4][monster.posX] = States::Watched;
				}
					
			}
		}
				
			
		//RIGHT PART
		if (monster.posY + 1 < gridSizeY && monster.posX + 1 < gridSizeX && grid[monster.posY + 1][monster.posX + 1] == States::Clear)
		{
			grid[monster.posY + 1][monster.posX + 1] = States::Watched;
			if (monster.posY + 2 < gridSizeY && monster.posX + 2 < gridSizeX && grid[monster.posY + 2][monster.posX + 2] == States::Clear)
				grid[monster.posY + 2][monster.posX + 2] = States::Watched;

			if (monster.posY + 2 < gridSizeY && monster.posX + 1 < gridSizeX && grid[monster.posY + 2][monster.posX + 1] == States::Clear)
			{
				grid[monster.posY + 2][monster.posX + 1] = States::Watched;
				if (monster.posY + 3 < gridSizeY && monster.posX + 1 < gridSizeX && grid[monster.posY + 3][monster.posX + 1] == States::Clear)
					grid[monster.posY + 3][monster.posX + 1] = States::Watched;
			}
				
		}
			
	
		//LEFT PART
		if (monster.posY + 1 < gridSizeY && monster.posX - 1 >= 0 && grid[monster.posY + 1][monster.posX - 1] == States::Clear)
		{
			grid[monster.posY + 1][monster.posX - 1] = States::Watched;
			if (monster.posY + 2 < gridSizeY && monster.posX - 2 >= 0 && grid[monster.posY + 2][monster.posX - 2] == States::Clear)
				grid[monster.posY + 2][monster.posX - 2] = States::Watched;

			if (monster.posY + 2 < gridSizeY && monster.posX - 1 >= 0 && grid[monster.posY + 2][monster.posX - 1] == States::Clear)
			{
				grid[monster.posY + 2][monster.posX - 1] = States::Watched;
				if (monster.posY + 3 < gridSizeY && monster.posX - 1 >= 0 && grid[monster.posY + 3][monster.posX - 1] == States::Clear)
					grid[monster.posY + 3][monster.posX - 1] = States::Watched;
			}
				
		}
			
	}
}

void Game::drawObstacles()
{
	grid[2][3] = States::Obstacle;
	grid[3][3] = States::Obstacle;
	grid[4][3] = States::Obstacle;
	grid[5][3] = States::Obstacle;

	grid[10][55] = States::Obstacle;
	grid[11][55] = States::Obstacle;
	grid[12][55] = States::Obstacle;
	grid[13][55] = States::Obstacle;

	grid[2][15] = States::Obstacle;
	grid[3][15] = States::Obstacle;
	grid[4][15] = States::Obstacle;
	grid[4][16] = States::Obstacle;
	grid[4][17] = States::Obstacle;
	grid[4][18] = States::Obstacle;

	grid[7][30] = States::Obstacle;
	grid[7][31] = States::Obstacle;
	grid[8][30] = States::Obstacle;
	grid[8][31] = States::Obstacle;

	grid[9][15] = States::Obstacle;
	grid[10][15] = States::Obstacle;
	grid[11][15] = States::Obstacle;
	grid[11][16] = States::Obstacle;
	grid[11][17] = States::Obstacle;
	grid[11][18] = States::Obstacle;

	grid[2][40] = States::Obstacle;
	grid[3][40] = States::Obstacle;
	grid[4][40] = States::Obstacle;
	grid[5][40] = States::Obstacle;
	grid[5][41] = States::Obstacle;
	grid[5][41] = States::Obstacle;

	grid[9][40] = States::Obstacle;
	grid[10][40] = States::Obstacle;
	grid[11][40] = States::Obstacle;
	grid[11][41] = States::Obstacle;
	grid[11][42] = States::Obstacle;
	grid[11][43] = States::Obstacle;

}