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

void Monster::move()
{
	//TODO
}

void Monster::place(int posX,int posY)
{
	this->posX = posX;
	this->posY = posY;
}