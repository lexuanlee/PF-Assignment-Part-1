#include <iostream>
#include <string>
#include <cstdlib>
#include "start.hpp"
#include "board.hpp"
#include "gameplay.hpp"
#include "func.h"
#include "trackerCon.hpp"

using namespace std;
using namespace func;

int totalZlife;

void zomAtk(Position *&zomPos, int numOfZombie, string **&board, int &alienLife, int *&zombieAttack, int &zrp, int &zcp, int *&zombieRange, int *&zombieLife, int &row, int &column, int &currentCount);
void zomTurn(Position *&zomPos, int numOfZombie, string **&board, int i, int &alienLife, int &alienAtk, int *&zombieAttack, int &arp, int &acp, int *&zombieRange, int *&zombieLife, string tracker);
void restartPrompt1();
void restartPrompt();

void zomAtk(Position *&zomPos, int numOfZombie, string **&board, int &alienLife, int *&zombieAttack, int &zrp, int &zcp, int *&zombieRange, int *&zombieLife, int &row, int &column, int &currentCount)
{
    zcp = zomPos[currentCount].cp;
    zrp = zomPos[currentCount].rp;
    int *zattack = &zombieAttack[currentCount];

    for (int a = 1; a <= zombieRange[currentCount] && zcp + a < column; a++)
    {

        if (board[zrp][zcp + a] == "A")
        {
            cout << "Zombie"
                 << " " << currentCount + 1 << " attack Alien with a damage of " << *zattack << endl;
            alienLife = alienLife - *zattack;
            if (alienLife <= 0)
            {
                cout << "You have been defeated by zombie, better luck next time!" << endl;
                pause();
                restartPrompt();
                return;
            }
            return;
        }
    }

    for (int a = 1; a <= zombieRange[currentCount] && zcp - a >= 0; a++)
    {
        if (board[zrp][zcp - a] == "A")
        {
            cout << "Zombie"
                 << " " << currentCount + 1 << " attack Alien with a damage of " << *zattack << endl;
            alienLife = alienLife - *zattack;
            if (alienLife <= 0)
            {
                cout << "You have been defeated by zombie, better luck next time!" << endl;
                pause();
                restartPrompt();
                return;
            }
            return;
        }
    }

    for (int a = 1; a <= zombieRange[currentCount] && zrp - a >= 0; a++)
    {
        if (board[zrp - a][zcp] == "A")
        {
            cout << "Zombie"
                 << " " << currentCount + 1 << " attack Alien with a damage of " << *zattack << endl;
            alienLife = alienLife - *zattack;
            if (alienLife <= 0)
            {
                cout << "You have been defeated by zombie, better luck next time!" << endl;
                pause();
                restartPrompt();
                return;
            }
            return;
        }
    }

    for (int a = 1; a <= zombieRange[currentCount] && zrp + a < row; a++)
    {
        if (board[zrp + a][zcp] == "A")
        {
            cout << "Zombie"
                 << " " << currentCount + 1 << " attack Alien with a damage of " << *zattack << endl;
            alienLife = alienLife - *zattack;
            if (alienLife <= 0)
            {
                cout << "You have been defeated by zombie, better luck next time!" << endl;
                pause();
                restartPrompt();
                return;
            }
            return;
        }
    }

    for (int i = 1; i <= zombieRange[currentCount] && zrp - i >= 0; i++)
    {

        for (int j = zombieRange[currentCount]; j > i && zcp + j - i < column; j--)
        {
            if (board[zrp - i][zcp + j - i] == "A")
            {
                cout << "Zombie"
                     << " " << currentCount + 1 << " attack Alien with a damage of " << *zattack << endl;
                alienLife = alienLife - *zattack;
                if (alienLife <= 0)
                {
                    cout << "You have been defeated by zombie, better luck next time!" << endl;
                    pause();
                    restartPrompt();
                    return;
                }
                return;
            }
        }
    }
    for (int i = 1; i <= zombieRange[currentCount] && zrp - i >= 0; i++)
    {
        // cout << "TEST6" << endl;
        // system("pause");
        // board[zrp - i][zcp];
        for (int j = zombieRange[currentCount]; j > i && zcp - j + i >= 0; j--)
        {
            if (board[zrp - i][zcp - j + i] == "A")
            {
                cout << "Zombie"
                     << " " << currentCount + 1 << " attack Alien with a damage of " << *zattack << endl;
                alienLife = alienLife - *zattack;
                if (alienLife <= 0)
                {
                    cout << "You have been defeated by zombie, better luck next time!" << endl;
                    pause();
                    restartPrompt();
                    return;
                }
                return;
            }
        }
    }
    for (int i = 1; i <= zombieRange[currentCount] && zrp + i < row; i++)
    {
        // cout << "TESTJ7" << endl;
        // system("pause");
        // board[zrp + i][zcp];
        for (int j = zombieRange[currentCount]; j > i && zcp + j - i < column; j--)
        {
            if (board[zrp + i][zcp + j - i] == "A")
            {
                cout << "Zombie"
                     << " " << currentCount + 1 << " attack Alien with a damage of " << *zattack << endl;
                alienLife = alienLife - *zattack;
                if (alienLife <= 0)
                {
                    cout << "You have been defeated by zombie, better luck next time!" << endl;
                    pause();
                    restartPrompt();
                    return;
                }
                return;
            }
        }
    }
    for (int i = 1; i <= zombieRange[currentCount] && zrp + i < row; i++)
    {
        // cout << "TESTJ8" << endl;
        // system("pause");
        // board[zrp + i][zcp];
        for (int j = zombieRange[currentCount]; j > i && zcp - j + i >= 0; j--)
        {
            if (board[zrp + i][zcp - j + i] == "A")
            {
                cout << "Zombie"
                     << " " << currentCount + 1 << " attack Alien with a damage of " << *zattack << endl;
                alienLife = alienLife - *zattack;
                if (alienLife <= 0)
                {
                    cout << "You have been defeated by zombie, better luck next time!" << endl;
                    pause();
                    restartPrompt();
                    return;
                }
                return;
            }
        }
        // cout << "TEST 8.5" << endl;

        // system("pause");
    }
    // system("pause");
    // cout << "TEST9" << endl;
    // system("pause");
    return;
}

void zomTurn(Position *&zomPos, int numOfZombie, string **&board, int i, int &alienLife, int &alienAtk, int *&zombieAttack, int &arp, int &acp, int *&zombieRange, int *&zombieLife, string tracker)
{
    int za = zombieAttack[i];
    // Accessing zombie positions
    // for (int i = 0; i < numOfZombie; i++)
    // {
    //     cout << zomPos[i].rp << " " << zomPos[i].cp << endl;
    // }

    // cout << "zomb range is" << zombieRange[i] << endl;
    // Accessing succeed. Proceed with code

    char charc = char(i);

    string movesets[] = {"1", "2", "3", "4"};
    string zomID[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

    int zrp = zomPos[i].rp;
    int zcp = zomPos[i].cp;

    // /test zomPos before
    // cout << "before: " << zomPos[i].rp << " " << zomPos[i].cp << endl;

    int zrpSave = zrp;
    int zcpSave = zcp;

    // string randmove = movesets[rand() % 4];
    string randmove = " ";
    // int randmove = rand() % 4 + 1;

    // fix this zombie identifier with isazombie = true by scoping true the board.

    if (tracker == "y")
    {
        trackerOn(zrp, zcp, arp, acp, row, column, board, randmove);
        // cout << "Tracker Mode: On" << endl;
        // cout << randmove << endl;
        // pause();
    }

    else if (tracker == "n")
    {
        trackerOff(zrp, zcp, row, column, board, randmove);
        // cout << "Tracker Mode: Off" << endl;
        // cout << randmove << endl;
        // pause();
    }

    if (randmove == "1") // move left
    {
        cout << "Zombie " << i + 1 << " moves left." << endl;
        zcp--;
        pause();
        zomPos[i].cp = zcp;

        // cout << "after : " << zomPos[i].rp << " " << zomPos[i].cp << endl;
        // system("PAUSE");

        board[zrp][zcp] = zomID[i];
        board[zrpSave][zcpSave] = " ";
        // printBoard(board, row, column);
        // disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
    }
    else if (randmove == "2")
    {
        cout << "Zombie " << i + 1 << " moves right." << endl;
        zcp++;
        pause();

        zomPos[i].cp = zcp;

        // // test zomPos after
        // cout << "after : " << zomPos[i].rp << " " << zomPos[i].cp << endl;
        // system("PAUSE");

        board[zrp][zcp] = zomID[i];
        board[zrpSave][zcpSave] = " ";
        // printBoard(board, row, column);
        // disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
    }

    else if (randmove == "3")
    {
        cout << "Zombie " << i + 1 << " move up." << endl;
        zrp--;
        system("PAUSE");

        zomPos[i].rp = zrp;

        // test zomPos after
        // cout << "after : " << zomPos[i].rp << " " << zomPos[i].cp << endl;
        // system("PAUSE");

        board[zrp][zcp] = zomID[i];
        board[zrpSave][zcpSave] = " ";
        // printBoard(board, row, column);
        // disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
    }
    else if (randmove == "4")
    {

        cout << "Zombie " << i + 1 << " moves down." << endl;
        zrp++;
        system("PAUSE");

        zomPos[i].rp = zrp;

        // test zomPos after
        // cout << "after : " << zomPos[i].rp << " " << zomPos[i].cp << endl;
        // system("PAUSE");

        board[zrp][zcp] = zomID[i];
        board[zrpSave][zcpSave] = " ";
        // printBoard(board, row, column);
        // disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
    }
    else
    {
        cout << "move not done" << endl;
    }
    // board[zrp][zcp] = zomID[i];
    // board[zrpSave][zcpSave] = " ";

    clear();
    printBoard(board, row, column);
    disCharinfotype2(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange, i);

    // cout << "Zombie " << i + 1 << "'s end turn." << endl;

    // system("PAUSE");
}

void restartPrompt1()
{
    cout << "Would you like to restart? y/n" << endl;
    cout << "Command: ";
    string restart;
    cin >> restart;
    cout << endl;
    if (restart == "y")
    {
        return;
    }

    else if (restart == "n")
    {
        cout << "Well, see you again soon!" << endl;
        pause();
        exit(0);
    }
    else
    {
        cout << "Invalid Response" << endl;
        restartPrompt1();
    }
}

void restartPrompt()
{
    cout << "Would you like to restart? y/n" << endl;
    cout << "Command: ";
    string restart;
    cin >> restart;
    cout << endl;
    if (restart == "y")
    {
        string restart = "y";
        while (restart == "y")
        {
            defaultSetting();

            clear();

            srand(time(NULL));

            // initialize board

            string **board = new string *[row];
            for (int i = 0; i < row; i++)
            {
                board[i] = new string[column];
            }

            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    int objNo = rand() % 40;
                    board[i][j] = objects[objNo];
                }
            }

            // initialize alien position
            int acp = column / 2;
            int arp = row / 2;

            board[arp][acp] = "A";

            // initialize alien life
            int alienLife = 100;

            // initialize aliean atk
            int alienAtk = 0;

            // initialize zombie position, make sure it is not the same as other zombies and alien
            string zomID[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

            Position *zomPos = new Position[numOfZombie];

            int zrp, zcp;

            for (int a = 0; a < numOfZombie; a++)
            {
                zcp = rand() % column;
                zrp = rand() % row;

                bool found = false;
                for (int b = 0; b < a; b++)
                {
                    if (zcp == zomPos[b].cp && zrp == zomPos[b].rp) // based on the zomPos , where b is the array seq of zombie, .cp takes the col pos, .rp takes row pos
                    {
                        found = true;
                        break;
                    }
                }

                if (found || (zcp == acp && zrp == arp))
                {
                    a--;
                    continue;
                }
                else
                {
                    zomPos[a].cp = zcp;
                    zomPos[a].rp = zrp;
                    board[zrp][zcp] = zomID[a];
                }
            }

            // initialize zombie life (zombie random life = zrl , zombie random attack = zra)
            int *zombieLife = new int[numOfZombie];
            int *zombieAttack = new int[numOfZombie];
            int *zombieRange = new int[numOfZombie];

            totalZlife = 0;

            for (int a = 0; a < numOfZombie; a++)
            {
                int zrl = rand() % 50 + 20;
                int zra = rand() % 25 + 5;
                int zrr;
                if (row <= column)
                {
                    zrr = rand() % (row - 2) + 1;
                }
                else if (column <= row)
                {
                    zrr = rand() % (column - 2) + 1;
                }

                zombieLife[a] = zrl;
                totalZlife = totalZlife + zombieLife[a];
                zombieAttack[a] = zra;
                zombieRange[a] = zrr;
            }

            bool alienWin = false;
            int diffZlife;
            int totalZlife2 = 100;

            while (alienLife > 0 && alienWin == false && totalZlife2 != 0)
            {

                // turn 1 - alien
                printBoard(board, row, column);
                disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                cmd(board, totalZlife, numOfZombie, row, column, arp, acp, zrp, zcp, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange, zomPos);

                cout << "Alien turn end. The trial resets." << endl;
                alienAtk = 0;

                for (int i = 0; i < row; i++)
                {
                    for (int j = 0; j < column; j++)
                    {
                        if (board[i][j] == ".")
                        {
                            int objNo = rand() % 40;
                            board[i][j] = objects[objNo];
                        }
                    }
                }
                clear();

                if (alienLife > 0 && totalZlife2 > 0)
                {

                    for (int currentCount = 0; currentCount < numOfZombie; currentCount++)
                    {
                        if (zombieLife[currentCount] > 0)
                        {
                            printBoard(board, row, column);
                            disCharinfotype2(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange, currentCount);
                            zomTurn(zomPos, numOfZombie, board, currentCount, alienLife, alienAtk, zombieAttack, arp, acp, zombieRange, zombieLife, tracker);
                            zomAtk(zomPos, numOfZombie, board, alienLife, zombieAttack, zrp, zcp, zombieRange, zombieLife, row, column, currentCount);
                            cout << "Zombie " << currentCount + 1 << "'s end turn." << endl;
                            pause();
                            clear();
                            // cout << zombieLife[currentCount] << endl;
                            // cout << totalZlife << endl;
                        }
                    }

                    totalZlife2 = 0;

                    for (int currentCount = 0; currentCount < numOfZombie; currentCount++)
                    {
                        totalZlife2 = totalZlife2 + zombieLife[currentCount];
                    }

                    if (totalZlife2 == 0)
                    {
                        cout << "Alien Wins!" << endl;
                        alienWin = true;
                        pause();
                        restartPrompt1();
                        break;
                    }
                }
            }
        }
    }

    else if (restart == "n")
    {
        cout << "Well, see you again soon!" << endl;
        pause();
        exit(0);
    }
    else
    {
        cout << "Invalid Response" << endl;
        restartPrompt1();
    }
}

int main()
{
    string restart = "y";
    while (restart == "y")
    {
        defaultSetting();

        clear();

        srand(time(NULL));

        // initialize board

        string **board = new string *[row];
        for (int i = 0; i < row; i++)
        {
            board[i] = new string[column];
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                int objNo = rand() % 40;
                board[i][j] = objects[objNo];
            }
        }

        // initialize alien position
        int acp = column / 2;
        int arp = row / 2;

        board[arp][acp] = "A";

        // initialize alien life
        int alienLife = 100;

        // initialize aliean atk
        int alienAtk = 0;

        // initialize zombie position, make sure it is not the same as other zombies and alien
        string zomID[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

        Position *zomPos = new Position[numOfZombie];

        int zrp, zcp;

        for (int a = 0; a < numOfZombie; a++)
        {
            zcp = rand() % column;
            zrp = rand() % row;

            bool found = false;
            for (int b = 0; b < a; b++)
            {
                if (zcp == zomPos[b].cp && zrp == zomPos[b].rp) // based on the zomPos , where b is the array seq of zombie, .cp takes the col pos, .rp takes row pos
                {
                    found = true;
                    break;
                }
            }

            if (found || (zcp == acp && zrp == arp))
            {
                a--;
                continue;
            }
            else
            {
                zomPos[a].cp = zcp;
                zomPos[a].rp = zrp;
                board[zrp][zcp] = zomID[a];
            }
        }

        // initialize zombie life (zombie random life = zrl , zombie random attack = zra)
        int *zombieLife = new int[numOfZombie];
        int *zombieAttack = new int[numOfZombie];
        int *zombieRange = new int[numOfZombie];

        totalZlife = 0;

        for (int a = 0; a < numOfZombie; a++)
        {
            int zrl = rand() % 50 + 20;
            int zra = rand() % 25 + 5;
            int zrr;
            if (row <= column)
            {
                zrr = rand() % (row - 2) + 1;
            }
            else if (column <= row)
            {
                zrr = rand() % (column - 2) + 1;
            }

            zombieLife[a] = zrl;
            totalZlife = totalZlife + zombieLife[a];
            zombieAttack[a] = zra;
            zombieRange[a] = zrr;
        }

        bool alienWin = false;
        int diffZlife;
        int totalZlife2 = 100;

        while (alienLife > 0 && alienWin == false && totalZlife2 != 0)
        {

            // turn 1 - alien
            printBoard(board, row, column);
            disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
            cmd(board, totalZlife, numOfZombie, row, column, arp, acp, zrp, zcp, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange, zomPos);

            cout << "Alien turn end. The trial resets." << endl;
            alienAtk = 0;

            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    if (board[i][j] == ".")
                    {
                        int objNo = rand() % 40;
                        board[i][j] = objects[objNo];
                    }
                }
            }
            clear();

            if (alienLife > 0 && totalZlife2 > 0)
            {

                for (int currentCount = 0; currentCount < numOfZombie; currentCount++)
                {
                    if (zombieLife[currentCount] > 0)
                    {
                        printBoard(board, row, column);
                        disCharinfotype2(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange, currentCount);
                        zomTurn(zomPos, numOfZombie, board, currentCount, alienLife, alienAtk, zombieAttack, arp, acp, zombieRange, zombieLife, tracker);
                        zomAtk(zomPos, numOfZombie, board, alienLife, zombieAttack, zrp, zcp, zombieRange, zombieLife, row, column, currentCount);
                        cout << "Zombie " << currentCount + 1 << "'s end turn." << endl;
                        pause();
                        clear();
                        // cout << zombieLife[currentCount] << endl;
                        // cout << totalZlife << endl;
                    }
                }

                totalZlife2 = 0;

                for (int currentCount = 0; currentCount < numOfZombie; currentCount++)
                {
                    totalZlife2 = totalZlife2 + zombieLife[currentCount];
                }

                if (totalZlife2 == 0)
                {
                    cout << "Alien Wins!" << endl;
                    alienWin = true;
                    pause();
                    restartPrompt1();
                    break;
                }
            }
        }
    }
}
