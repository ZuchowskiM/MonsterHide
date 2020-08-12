#ifndef Game_h
#define Game_h
#include"Human.h"
#include"Monster.h"
#include"Diamond.h"
#include<vector>

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

	std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> path;
	int monsterTargetPointX;
	int monsterTargetPointY;
	bool monsterTargetActive;

	bool diamondOnBoard;

	

	void Analize();
	void constructMonsterPath();
	virtual void show() = 0;

public:
	void getPlayerMove(int keyNumber);
	
	
};

#endif


