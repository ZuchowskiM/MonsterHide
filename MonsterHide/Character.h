#ifndef Character_h
#define Character_h

class Character
{
protected:
	int posX;
	int posY;

	Character();
	Character(int posX, int posY);
	~Character();

	virtual void place(int posX, int posY) = 0;

};

#endif

