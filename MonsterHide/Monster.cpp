#include "Monster.h"

Monster::Monster(): 
	Character()
{
	direction = Directions::right;
	destination = -1;
}

Monster::Monster(int posX, int posY) : 
	Character(posX, posY)
{
	direction = Directions::right;
	destination = -1;
}

Monster::~Monster()
{
	//EMPTY
}

void Monster::makeStep(int goToX, int goToY)
{
	if (goToY == posY - 1)
	{
		posY--;
		direction = Directions::up;
	}
	else if(goToY == posY + 1)
	{
		posY++;
		direction = Directions::down;
	}
	else if (goToX == posX + 1)
	{
		posX++;
		direction = Directions::right;
	}
	else if (goToX == posX - 1)
	{
		posX--;
		direction = Directions::left;
	}
}

void Monster::place(int posX,int posY)
{
	this->posX = posX;
	this->posY = posY;
}