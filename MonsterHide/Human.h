#ifndef Human_h
#define Human_h
#include "Character.h"

class Human :
	public Character
{
friend class Game;

private:
	Human(const Human& h);
	Human& operator=(const Human& h);


	Human();
	Human(int posX, int posY);
	~Human();

	void place(int posX, int posY);
};

#endif



