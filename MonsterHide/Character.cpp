#include "Character.h"

Character::Character()
{
	posX = 0;
	posY = 0;

}

Character::Character(int posX, int posY)
{
	this->posX = posX;
	this->posY = posY;
}

Character::~Character()
{
	//EMPTY
}
