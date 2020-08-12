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
	
    while (true)
    {
        system("cls");
        g1.show();

        int c = 0;
        while (!flag)
        {
            c = 0;

            switch ((c = _getch())) {
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
        g1.getPlayerMove(c);
    }

		//system("cls");
	//}

	return 0;
}