#ifndef Game_h
#define Game_h
#include"Human.h"
#include"Monster.h"
#include"Diamond.h"

class Game
{
private:
	Game(const Game& g);
	Game& operator=(const Game& g);

protected:
	Game();
	~Game();
	
	Human player;
	Monster monster;
	Diamond diamond;

	enum class States
	{
		Clear = 0,
		Watched = 1,
		Obstacle = 3,
		Player = 4,
		Monster = 5,
		Diamond = 6
	};

	States** grid;
	int gridSizeX;
	int gridSizeY;

	int movesCount;
	int diamondsCount;

	void Analize();
	virtual void show() = 0;
	
};

#endif


