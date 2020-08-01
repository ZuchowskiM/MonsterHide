#include "Human.h"

Human::Human(): 
	Character()
{
	//EMPTY
}

Human::Human(int posX, int posY) :
	Character(posX, posY)
{
	//EMPTY
}

Human::~Human()
{
	//EMPTY
}

void Human::place(int posX, int posY)
{
	this->posX = posX;
	this->posY = posY;
}