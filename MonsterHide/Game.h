#ifndef Game_h
#define Game_h
#include"Human.h"
#include"Monster.h"
#include"Diamond.h"
#include<vector>
#include<cmath>
#include<algorithm>

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

	int diamondsCount;

	std::vector<std::pair<int,int>> path;
	int monsterPathCurrentStep;
	int monsterTargetPointX;
	int monsterTargetPointY;
	bool monsterTargetActive;

	bool diamondOnBoard;

	bool gameEnd;

	void Analize();
	void constructMonsterPath();
	void drawMonsterVison();
	void drawObstacles();
	virtual bool show() = 0;

public:
	void getPlayerMove(int keyNumber);
	
	
};

#endif


