#ifndef Diamond_h
#define Diamond_h

class Diamond
{
friend class Game;
	Diamond();
	Diamond(int posX, int posY);
	~Diamond();

	int posX;
	int posY;
};

#endif


