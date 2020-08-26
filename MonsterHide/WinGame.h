#ifndef WinGame_h
#define WinGame_h

#include "Game.h"
#include<windows.h>

class WinGame :
	public Game
{
private:
	WinGame(const WinGame& wg);
	WinGame& operator=(const WinGame& wg);
	HANDLE hout;

public:
	WinGame();
	~WinGame();

	bool show();
	void writeInstruction();
};

#endif



