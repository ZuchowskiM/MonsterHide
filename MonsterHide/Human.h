#ifndef Human_h
#define Human_h
#include "Character.h"

class Human :
	public Character
{
friend class Game;
	Human();
	Human(int posX, int posY);
	~Human();

	void place(int posX, int posY);
};

#endif // !Human_h



