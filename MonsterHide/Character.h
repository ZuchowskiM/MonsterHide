#ifndef Character_h
#define Character_h

class Character
{
private:
	Character(const Character& c);
	Character& operator=(const Character& c);

public:
	int posX;
	int posY;

	Character();
	Character(int posX, int posY);
	~Character();

	virtual void place(int posX, int posY) = 0;

};

#endif

