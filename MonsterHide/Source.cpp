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
    

    int menu = 0;
    bool close = false;

    WinGame g1;
    bool flag = false;
    bool endGame = false;

    while (!close)
    {
        system("cls");
        cout << "Wpisz 1 aby rozpoczac gre" << endl;
        cout << "Wpisz 2 aby dowiedziec sie zasad gry" << endl;
        cout << "Wpisz 3 aby wyjsc" << endl;
        cin >> menu;

        switch (menu)
        {
        case 1:
            while (!endGame)
            {
                system("cls");
                endGame = g1.show();

                if (endGame)
                {
                    close = true;
                    break;
                }
                    

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
            break;
        case 2:
            system("cls");
            g1.writeInstruction();
            cout << "Nacisnij dowolny klawisz aby powrocic do menu" << endl;
            system("pause");
            break;
        case 3:
            close = true;
            break;
        default:
            system("cls");
            cout << "Podaj poprawna wartosc" << endl;
            Sleep(1500);
            break;
        }
    }
    
	return 0;
}