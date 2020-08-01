#ifndef Diamond_h
#define Diamond_h

class Diamond
{
friend class Game;
private:
	Diamond(const Diamond& d);
	Diamond& operator=(const Diamond& d);

	Diamond();
	Diamond(int posX, int posY);
	~Diamond();

	int posX;
	int posY;
};

#endif


