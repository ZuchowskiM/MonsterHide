#ifndef Monster_h
#define Monster_h

#include "Character.h"
class Monster :
	public Character
{
friend class Game;

	Monster();
	Monster(int posX,int posY);
	~Monster();


	enum class Directions
	{
		up = 0,
		right = 1,
		down = 2,
		left = 3
	};

	Directions direction;
	int destination;

	void move();
	void place(int posX,int posY);



};

#endif





