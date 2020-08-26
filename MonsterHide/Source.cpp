#include<iostream>
#include<conio.h>
#include"WinGame.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using std::cout;
using std::cin;
using std::endl;

int main()
{


	WinGame g1;
    bool flag = false;
    bool endGame = false;
	
    while (!endGame)
    {
        system("cls");
        endGame = g1.show();

        if (endGame)
            break;

        int key = 0;
        while (!flag)
        {
            key = 0;

            switch ((key = _getch())) {
            case KEY_UP:
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
                flag = true;
                break;
            default:
                break;
            }

        }
        flag = false;
        g1.getPlayerMove(key);
    }


	return 0;
}