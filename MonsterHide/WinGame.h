#ifndef WinGame_h
#define WinGame_h

#include "Game.h"
class WinGame :
	public Game
{
private:
	WinGame(const WinGame& wg);
	WinGame& operator=(const WinGame& wg);

public:
	WinGame();
	~WinGame();

	void show();
};

#endif



