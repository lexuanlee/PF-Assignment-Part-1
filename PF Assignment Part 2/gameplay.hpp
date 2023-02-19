#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <climits>
#include "help.hpp"
#include "struct.h"
#include "save.hpp"
#include "load.hpp"
#include "board.hpp"

using namespace std;

void cmd(string **&board, int &totalZlife, int &numOfZombie, int &row, int &column, int &arp, int &acp, int &zrp, int &zcp, int &alienLife, int &alienAtk, int *&zombieLife, int *&zombieAttack, int *&zombieRange, Position *&zomPos);
void disCharinfotype1(int &alienLife, int &alienAtk, int numOfZombie, int *zombieLife, int *zombieAttack, int *zombieRange);
void disCharinfotype2(int alienLife, int alienAtk, int numOfZombie, int *zombieLife, int *zombieAttack, int *zombieRange, int currentCount);
void restartPrompt2();

double nearest_distance(int &zrp, int &zcp, int &arp, int &acp)
{
    return sqrt(pow(zcp - acp, 2) + pow(zrp - arp, 2));
}

void find_nearest_zomb(string **board, Position *zomPos, int &numOfZombie, int &row, int &column, int &zrp, int &zcp, int &arp, int &acp, int *zombieLife)
{
    double maxDistance = INT_MAX;
    int nearest_Zom_index = 0;
    // cout << "TEST!!" << endl;
    // system("PAUSE");
    for (int i = 0; i < numOfZombie; i++)
    {
        zrp = zomPos[i].rp;
        zcp = zomPos[i].cp;
        double d = nearest_distance(zrp, zcp, arp, acp);
        // cout << numOfZombie << endl;
        // cout << d << endl;
        // system("PAUSE");
        if (d < maxDistance)
        {
            maxDistance = d;
            nearest_Zom_index = i;
            // cout << "zombie now is this nombor" << i << endl;
        }
    }

    int closestRow = zomPos[nearest_Zom_index].rp;
    int closestColumn = zomPos[nearest_Zom_index].cp;
    cout << "Zombie " << nearest_Zom_index + 1 << " receive a damage of 10" << endl;
    zombieLife[nearest_Zom_index] -= 10;
    if (zombieLife[nearest_Zom_index] > 0)
    {
        cout << "Zombie " << nearest_Zom_index + 1 << " is still alive" << endl;
    }
    else
    {
        cout << "Zombie " << nearest_Zom_index + 1 << " is defeated." << endl;
        board[zrp][zcp] = " ";
    }
    return;
}

void restartPrompt2()
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
        system("pause");
        exit(0);
    }
    else
    {
        cout << "Invalid Response" << endl;
        restartPrompt2();
    }
}

void cmd(string **&board, int &totalZlife, int &numOfZombie, int &row, int &column, int &arp, int &acp, int &zrp, int &zcp, int &alienLife, int &alienAtk, int *&zombieLife, int *&zombieAttack, int *&zombieRange, Position *&zomPos)
{
    string command;
    cout << "Command: ";
    cin >> command;

    if (command == "quit")
    {
        string quit;
        cout << "Are you sure ? (y/n) > ";
        cin >> quit;
        if (quit == "y")
        {
            exit(0);
        }
        else if (quit == "n")
        {
            system("cls");
            printBoard(board, row, column);
            disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
            cmd(board, totalZlife, numOfZombie, row, column, arp, acp, zrp, zcp, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange, zomPos);
        }
        else
        {
            cout << "Invalid response." << endl;
            system("pause");
            system("cls");
            printBoard(board, row, column);
            disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
            cmd(board, totalZlife, numOfZombie, row, column, arp, acp, zrp, zcp, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange, zomPos);
        }
    }
    else if (command == "new")
    {
        system("cls");

        for (int i = 0; i < row; i++)
        {
            delete[] board[i];
        }
        delete[] board;

        delete[] zomPos;
        delete[] zombieLife;
        delete[] zombieAttack;
        delete[] zombieRange;

        board = new string *[row];
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

        acp = column / 2;
        arp = row / 2;

        board[arp][acp] = "A";

        string zomID[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

        zomPos = new Position[numOfZombie];

        for (int a = 0; a < numOfZombie; a++)
        {
            int zcp = rand() % column;
            int zrp = rand() % row;

            // cout << zcp << " " << zrp << endl;

            bool found = false;
            for (int b = 0; b < a; b++)
            {
                if (zcp == zomPos[b].cp && zrp == zomPos[b].rp)
                {
                    found = true;
                    break;
                }
            }

            if (found || (zcp == acp && zrp == arp))
            {
                a--;
                // cout << "found" << endl;
                continue;
            }
            else
            {
                zomPos[a].cp = zcp;
                zomPos[a].rp = zrp;
                board[zrp][zcp] = zomID[a];
            }
        }

        // initialize alien life
        alienLife = 100;

        // initialize aliean atk
        alienAtk = 0;

        // initialize zombie life (zombie random life = zrl , zombie random attack = zra)
        zombieLife = new int[numOfZombie];
        zombieAttack = new int[numOfZombie];
        zombieRange = new int[numOfZombie];

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

            // cout << totalZlife << endl;
            // system("pause");
        }

        printBoard(board, row, column);
        disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
        cmd(board, totalZlife, numOfZombie, row, column, arp, acp, zrp, zcp, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange, zomPos);
    }
    else if (command == "arrow")
    {
        int c, r;
        string arrow;
        cout << "Enter the column number,row number and the arrow that you wish to change. Eg: 3 2 >  :" << endl;
        cin >> c >> r >> arrow;
        if (arrow == "v" || arrow == "^" || arrow == "<" || arrow == ">")
        {
            if (board[r - 1][c - 1] == "v" || board[r - 1][c - 1] == "^" || board[r - 1][c - 1] == ">" || board[r - 1][c - 1] == "<")
            {
                board[r - 1][c - 1] = arrow;
            }
            else
            {
                cout << "Cheating!" << endl;
                system("pause");
            }

            // cout << "Arrow " << board[c][r] << " is changed to " << arrow << endl;
            system("cls");
            printBoard(board, row, column);
            disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
            cmd(board, totalZlife, numOfZombie, row, column, arp, acp, zrp, zcp, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange, zomPos);
        }
        else
        {
            cout << "Invalid response." << endl;
            system("pause");
            system("cls");

            printBoard(board, row, column);
            disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
            cmd(board, totalZlife, numOfZombie, row, column, arp, acp, zrp, zcp, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange, zomPos);
        }
    }
    else if (command == "help")
    {
        help();
        system("pause");
        system("cls");
        printBoard(board, row, column);
        disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
        cmd(board, totalZlife, numOfZombie, row, column, arp, acp, zrp, zcp, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange, zomPos);
    }
    else if (command == "save")
    {
        string filename;
        cout << "Enter the file name to save the current game (Eg: game1.txt): " << endl;
        cin >> filename;
        saveFile(filename, board, row, column, arp, acp, numOfZombie, zomPos, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange);
        system("cls");

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (board[i][j] == "*")
                {
                    board[i][j] = " ";
                }
            }
        }
        printBoard(board, row, column);
        disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
        cmd(board, totalZlife, numOfZombie, row, column, arp, acp, zrp, zcp, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange, zomPos);
    }
    else if (command == "load")
    {
        // before loading, prompt save
        string save;

        while (true)
        {
            cout << endl;
            cout << "Would you like to save your progress? y/n >";
            cin >> save;

            if (save == "y")
            {
                string filename;
                cout << endl;
                cout << "Enter the file name to save the current game (Eg: game1.txt): " << endl;
                cin >> filename;
                saveFile(filename, board, row, column, arp, acp, numOfZombie, zomPos, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange);
                break;
            }
            else if (save == "n")
            {
                break;
            }
            else
            {
                cout << endl;
                cout << "Invalid Input" << endl;
            }
            system("pause");
            system("cls");
            printBoard(board, row, column);
            disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
        }

        // clear saving notations
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (board[i][j] == "*")
                {
                    board[i][j] = " ";
                }
            }
        }

        system("cls");
        printBoard(board, row, column);
        disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);

        // loading dimension work but not playable because the dimension goes back to normal

        bool unableOpen = false;
        string filename;
        cout << endl;
        cout << "Loading File " << endl;
        cout << "------------------------" << endl;
        cout << "Please input filename: ";
        cin >> filename;
        // load board
        loadFile(unableOpen, filename, board, row, column, arp, acp, numOfZombie, zomPos, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange);
        // reload board to correct stats
        loadFile(unableOpen, filename, board, row, column, arp, acp, numOfZombie, zomPos, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange);
        if (unableOpen == true)
        {
            cout << "Unable to open " << filename << endl;
            unableOpen = false;
        }
        system("pause");
        system("cls");

        printBoard(board, row, column);
        disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
        cmd(board, totalZlife, numOfZombie, row, column, arp, acp, zrp, zcp, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange, zomPos);
    }
    else if (command == "left" || command == "right" || command == "up" || command == "down")
    {
        if (command == "left")
        {
        left:
            while (acp > 0)
            {
                int arpSave = arp;
                int acpSave = acp;

                acp--;

                if (board[arp][acp] == " ")
                {
                    cout << "Alien finds an empty space." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == ".")
                {
                    cout << "It is an empty trail." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == "v")
                {
                    cout << "Alien finds an arrow and moves down." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto down;
                }
                else if (board[arp][acp] == "^")
                {
                    cout << "Alien finds an arrow and moves up." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto up;
                }
                else if (board[arp][acp] == "<")
                {
                    cout << "Alien finds an arrow and moves left." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto left;
                }
                else if (board[arp][acp] == ">")
                {
                    cout << "Alien finds an arrow and moves right." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto right;
                }
                else if (board[arp][acp] == "h")
                {
                    cout << "Alien finds a health pack." << endl;
                    if (alienLife < 100)
                    {
                        alienLife += 20;
                        cout << "Alien's life is increased by 20. (max life of Alien = 100)" << endl;
                        if (alienLife > 100)
                        {
                            alienLife = 100;
                        }
                    }
                    else
                    {
                        alienLife += 0;
                    }
                    system("PAUSE");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    // bool alienLifeInc = true; // need check
                }
                else if (board[arp][acp] == "p")
                {
                    cout << "Alien finds a pod." << endl;
                    find_nearest_zomb(board, zomPos, numOfZombie, row, column, zrp, zcp, arp, acp, zombieLife); // which nearest zombie kena damage?
                    /*if (zombieLife > 0)
                    {
                        cout << "Zombie [] is still alive" << endl;
                    }
                    else
                    {
                        cout << "Zombie [] is defeated." << endl;
                        zombie () position = " ";
                    }*/
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == "r")
                {
                    cout << "Alien stumbles upon a rock." << endl;
                    int randnum = rand() % 11;
                    board[arp][acp] = objects[randnum];
                    cout << "Alien discovers a ' " << objects[randnum] << " ' beneath the rock." << endl;
                    system("pause");
                    acp++;
                    break;
                }
                else if (board[arp][acp] == "o")
                {
                    cout << "Alien finds a poison." << endl;
                    if (alienLife > 10)
                    {
                        alienLife -= 10;
                        cout << "Opps, Alien's life is decreased by 10." << endl;
                        board[arp][acp] = "A";
                    }
                    else
                    {
                        alienLife = 0;
                        cout << "Alien is defeated. Game Over" << endl;
                        board[arp][acp] = " ";
                        system("PAUSE");
                        restartPrompt2();
                        return;
                    }
                    system("PAUSE");
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == "1")
                {
                    cout << "Alien meets zombie 1." << endl;
                    cout << "Zombie 1 receives a damage of " << alienAtk << endl;
                    zombieLife[0] -= alienAtk;
                    if (zombieLife[0] <= 0)
                    {
                        zombieLife[0] = 0;
                        cout << "Zombie 1 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "2")
                {
                    cout << "Alien meets zombie 2." << endl;
                    cout << "Zombie 2 receives a damage of " << alienAtk << endl;
                    zombieLife[1] -= alienAtk;
                    if (zombieLife[1] <= 0)
                    {
                        zombieLife[1] = 0;
                        cout << "Zombie 2 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "3")
                {
                    cout << "Alien meets zombie 3." << endl;
                    cout << "Zombie 3 receives a damage of " << alienAtk << endl;
                    zombieLife[2] -= alienAtk;
                    if (zombieLife[2] <= 0)
                    {
                        zombieLife[2] = 0;
                        cout << "Zombie 3 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "4")
                {
                    cout << "Alien meets zombie 4." << endl;
                    cout << "Zombie 4 receives a damage of " << alienAtk << endl;
                    zombieLife[3] -= alienAtk;
                    if (zombieLife[3] <= 0)
                    {
                        zombieLife[3] = 0;
                        cout << "Zombie 4 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "5")
                {
                    cout << "Alien meets zombie 5." << endl;
                    cout << "Zombie 5 receives a damage of " << alienAtk << endl;
                    zombieLife[4] -= alienAtk;
                    if (zombieLife[4] <= 0)
                    {
                        zombieLife[4] = 0;
                        cout << "Zombie 5 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "6")
                {
                    cout << "Alien meets zombie 6." << endl;
                    cout << "Zombie 6 receives a damage of " << alienAtk << endl;
                    zombieLife[5] -= alienAtk;
                    if (zombieLife[5] <= 0)
                    {
                        zombieLife[5] = 0;
                        cout << "Zombie 6 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "7")
                {
                    cout << "Alien meets zombie 7." << endl;
                    cout << "Zombie 7 receives a damage of " << alienAtk << endl;
                    zombieLife[6] -= alienAtk;
                    if (zombieLife[6] <= 0)
                    {
                        zombieLife[6] = 0;
                        cout << "Zombie 1 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "8")
                {
                    cout << "Alien meets zombie 8." << endl;
                    cout << "Zombie 8 receives a damage of " << alienAtk << endl;
                    zombieLife[7] -= alienAtk;
                    if (zombieLife[7] <= 0)
                    {
                        zombieLife[7] = 0;
                        cout << "Zombie 8 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "9")
                {
                    cout << "Alien meets zombie 9." << endl;
                    cout << "Zombie 9 receives a damage of " << alienAtk << endl;
                    zombieLife[8] -= alienAtk;
                    if (zombieLife[8] <= 0)
                    {
                        zombieLife[9] = 0;
                        cout << "Zombie 9 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp++;
                    bool alienAttackInc = true;
                    break;
                }
                else
                {
                    break;
                }
                system("cls");
                printBoard(board, row, column);
                disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
            }
        }
        else if (command == "right")
        {
        right:
            while (acp < column - 1)
            {
                int arpSave = arp;
                int acpSave = acp;
                acp++;
                // printBoard(board, row, column);
                // system("cls");
                //  system("pause");

                if (board[arp][acp] == " ")
                {
                    cout << "Alien finds an empty space." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == ".")
                {
                    cout << "It is an empty trail." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == "v")
                {
                    cout << "Alien finds an arrow and moves down." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto down;
                }
                else if (board[arp][acp] == "^")
                {
                    cout << "Alien finds an arrow and moves up." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto up;
                }
                else if (board[arp][acp] == "<")
                {
                    cout << "Alien finds an arrow and moves left." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto left;
                }
                else if (board[arp][acp] == ">")
                {
                    cout << "Alien finds an arrow and moves right." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto right;
                }
                else if (board[arp][acp] == "h")
                {
                    cout << "Alien finds a health pack." << endl;
                    if (alienLife < 100)
                    {
                        alienLife += 20;
                        cout << "Alien's life is increased by 20. (max life of Alien = 100)" << endl;
                        if (alienLife > 100)
                        {
                            alienLife = 100;
                        }
                    }
                    else
                    {
                        alienLife += 0;
                    }
                    system("PAUSE");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    // bool alienLifeInc = true; // need check
                }
                else if (board[arp][acp] == "p")
                {
                    cout << "Alien finds a pod." << endl;
                    find_nearest_zomb(board, zomPos, numOfZombie, row, column, zrp, zcp, arp, acp, zombieLife); // which nearest zombie kena damage?
                                                                                                                // which nearest zombie kena damage?
                    /*if (zombieLife > 0)
                    {
                        cout << "Zombie [] is still alive" << endl;
                    }
                    else
                    {
                        cout << "Zombie [] is defeated." << endl;
                        zombie () position = " ";
                    }*/
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == "r")
                {
                    cout << "Alien stumbles upon a rock." << endl;
                    int randnum = rand() % 11;
                    board[arp][acp] = objects[randnum];
                    cout << "Alien discovers a ' " << objects[randnum] << " ' beneath the rock." << endl;
                    system("pause");
                    acp--;
                    break;
                }
                else if (board[arp][acp] == "o")
                {
                    cout << "Alien finds a poison." << endl;
                    if (alienLife > 10)
                    {
                        alienLife -= 10;
                        cout << "Opps, Alien's life is decreased by 10." << endl;
                        board[arp][acp] = "A";
                    }
                    else
                    {
                        alienLife = 0;
                        cout << "Alien is defeated. Game Over" << endl;
                        board[arp][acp] = " ";
                        system("PAUSE");
                        restartPrompt2();
                        return;
                    }
                    system("PAUSE");
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == "1")
                {
                    cout << "Alien meets zombie 1." << endl;
                    cout << "Zombie 1 receives a damage of " << alienAtk << endl;
                    zombieLife[0] -= alienAtk;
                    if (zombieLife[0] <= 0)
                    {
                        zombieLife[0] = 0;
                        cout << "Zombie 1 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "2")
                {
                    cout << "Alien meets zombie 2." << endl;
                    cout << "Zombie 2 receives a damage of " << alienAtk << endl;
                    zombieLife[1] -= alienAtk;
                    if (zombieLife[1] <= 0)
                    {
                        zombieLife[1] = 0;
                        cout << "Zombie 2 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "3")
                {
                    cout << "Alien meets zombie 3." << endl;
                    cout << "Zombie 3 receives a damage of " << alienAtk << endl;
                    zombieLife[2] -= alienAtk;
                    if (zombieLife[2] <= 0)
                    {
                        zombieLife[2] = 0;
                        cout << "Zombie 3 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "4")
                {
                    cout << "Alien meets zombie 4." << endl;
                    cout << "Zombie 4 receives a damage of " << alienAtk << endl;
                    zombieLife[3] -= alienAtk;
                    if (zombieLife[3] <= 0)
                    {
                        zombieLife[3] = 0;
                        cout << "Zombie 4 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "5")
                {
                    cout << "Alien meets zombie 5." << endl;
                    cout << "Zombie 5 receives a damage of " << alienAtk << endl;
                    zombieLife[4] -= alienAtk;
                    if (zombieLife[4] <= 0)
                    {
                        zombieLife[4] = 0;
                        cout << "Zombie 5 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "6")
                {
                    cout << "Alien meets zombie 6." << endl;
                    cout << "Zombie 6 receives a damage of " << alienAtk << endl;
                    zombieLife[5] -= alienAtk;
                    if (zombieLife[5] <= 0)
                    {
                        zombieLife[5] = 0;
                        cout << "Zombie 6 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "7")
                {
                    cout << "Alien meets zombie 7." << endl;
                    cout << "Zombie 7 receives a damage of " << alienAtk << endl;
                    zombieLife[6] -= alienAtk;
                    if (zombieLife[6] <= 0)
                    {
                        zombieLife[6] = 0;
                        cout << "Zombie 1 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "8")
                {
                    cout << "Alien meets zombie 8." << endl;
                    cout << "Zombie 8 receives a damage of " << alienAtk << endl;
                    zombieLife[7] -= alienAtk;
                    if (zombieLife[7] <= 0)
                    {
                        zombieLife[7] = 0;
                        cout << "Zombie 8 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "9")
                {
                    cout << "Alien meets zombie 9." << endl;
                    cout << "Zombie 9 receives a damage of " << alienAtk << endl;
                    zombieLife[8] -= alienAtk;
                    if (zombieLife[8] <= 0)
                    {
                        zombieLife[8] = 0;
                        cout << "Zombie 9 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    acp--;
                    bool alienAttackInc = true;
                    break;
                }
                else
                {
                    break;
                }
                system("cls");
                printBoard(board, row, column);
                disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
            }
        }
        else if (command == "up")
        {
        up:
            while (arp > 0)
            {
                int arpSave = arp;
                int acpSave = acp;

                arp--;

                // printBoard(board, row, column);
                //  system("pause");

                if (board[arp][acp] == " ")
                {
                    cout << "Alien finds an empty space." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == ".")
                {
                    cout << "It is an empty trail." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == "v")
                {
                    cout << "Alien finds an arrow and moves down." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto down;
                }
                else if (board[arp][acp] == "^")
                {
                    cout << "Alien finds an arrow and moves up." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto up;
                }
                else if (board[arp][acp] == "<")
                {
                    cout << "Alien finds an arrow and moves left." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto left;
                }
                else if (board[arp][acp] == ">")
                {
                    cout << "Alien finds an arrow and moves right." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto right;
                }
                else if (board[arp][acp] == "h")
                {
                    cout << "Alien finds a health pack." << endl;
                    if (alienLife < 100)
                    {
                        alienLife += 20;
                        cout << "Alien's life is increased by 20. (max life of Alien = 100)" << endl;
                        if (alienLife > 100)
                        {
                            alienLife = 100;
                        }
                    }
                    else
                    {
                        alienLife += 0;
                    }
                    system("PAUSE");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    // bool alienLifeInc = true; // need check
                }
                else if (board[arp][acp] == "p")
                {
                    cout << "Alien finds a pod." << endl;
                    find_nearest_zomb(board, zomPos, numOfZombie, row, column, zrp, zcp, arp, acp, zombieLife);
                    // which nearest zombie kena damage?
                    // which nearest zombie kena damage?
                    /*if (zombieLife > 0)
                    {
                        cout << "Zombie [] is still alive" << endl;
                    }
                    else
                    {
                        cout << "Zombie [] is defeated." << endl;
                        zombie () position = " ";
                    }*/
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == "r")
                {
                    cout << "Alien stumbles upon a rock." << endl;
                    int randnum = rand() % 11;
                    board[arp][acp] = objects[randnum];
                    cout << "Alien discovers a ' " << objects[randnum] << " ' beneath the rock." << endl;
                    system("pause");
                    arp++;
                    break;
                }
                else if (board[arp][acp] == "o")
                {
                    cout << "Alien finds a poison." << endl;
                    if (alienLife > 10)
                    {
                        alienLife -= 10;
                        cout << "Opps, Alien's life is decreased by 10." << endl;
                        board[arp][acp] = "A";
                    }
                    else
                    {
                        alienLife = 0;
                        cout << "Alien is defeated. Game Over" << endl;
                        board[arp][acp] = " ";
                        system("PAUSE");
                        restartPrompt2();
                        return;
                    }
                    system("PAUSE");
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == "1")
                {
                    cout << "Alien meets zombie 1." << endl;
                    cout << "Zombie 1 receives a damage of " << alienAtk << endl;
                    zombieLife[0] -= alienAtk;
                    if (zombieLife[0] <= 0)
                    {
                        zombieLife[0] = 0;
                        cout << "Zombie 1 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "2")
                {
                    cout << "Alien meets zombie 2." << endl;
                    cout << "Zombie 2 receives a damage of " << alienAtk << endl;
                    zombieLife[1] -= alienAtk;
                    if (zombieLife[1] <= 0)
                    {
                        zombieLife[1] = 0;
                        cout << "Zombie 2 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "3")
                {
                    cout << "Alien meets zombie 3." << endl;
                    cout << "Zombie 3 receives a damage of " << alienAtk << endl;
                    zombieLife[2] -= alienAtk;
                    if (zombieLife[2] <= 0)
                    {
                        zombieLife[2] = 0;
                        cout << "Zombie 3 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "4")
                {
                    cout << "Alien meets zombie 4." << endl;
                    cout << "Zombie 4 receives a damage of " << alienAtk << endl;
                    zombieLife[3] -= alienAtk;
                    if (zombieLife[3] <= 0)
                    {
                        zombieLife[3] = 0;
                        cout << "Zombie 4 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "5")
                {
                    cout << "Alien meets zombie 5." << endl;
                    cout << "Zombie 5 receives a damage of " << alienAtk << endl;
                    zombieLife[4] -= alienAtk;
                    if (zombieLife[4] <= 0)
                    {
                        zombieLife[4] = 0;
                        cout << "Zombie 5 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "6")
                {
                    cout << "Alien meets zombie 6." << endl;
                    cout << "Zombie 6 receives a damage of " << alienAtk << endl;
                    zombieLife[5] -= alienAtk;
                    if (zombieLife[5] <= 0)
                    {
                        zombieLife[5] = 0;
                        cout << "Zombie 6 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "7")
                {
                    cout << "Alien meets zombie 7." << endl;
                    cout << "Zombie 7 receives a damage of " << alienAtk << endl;
                    zombieLife[6] -= alienAtk;
                    if (zombieLife[6] <= 0)
                    {
                        zombieLife[6] = 0;
                        cout << "Zombie 1 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "8")
                {
                    cout << "Alien meets zombie 8." << endl;
                    cout << "Zombie 8 receives a damage of " << alienAtk << endl;
                    zombieLife[7] -= alienAtk;
                    if (zombieLife[7] <= 0)
                    {
                        zombieLife[7] = 0;
                        cout << "Zombie 8 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp++;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "9")
                {
                    cout << "Alien meets zombie 9." << endl;
                    cout << "Zombie 9 receives a damage of " << alienAtk << endl;
                    zombieLife[8] -= alienAtk;
                    if (zombieLife[8] <= 0)
                    {
                        zombieLife[8] = 0;
                        cout << "Zombie 9 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp++;
                    bool alienAttackInc = true;
                    break;
                }
                else
                {
                    break;
                }
                system("cls");
                printBoard(board, row, column);
                disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
            }
        }
        else if (command == "down")
        {
        down:
            while (arp < row - 1)
            {
                int arpSave = arp;
                int acpSave = acp;
                arp++;
                // printBoard(board, row, column);
                //  system("pause");

                if (board[arp][acp] == " ")
                {
                    cout << "Alien finds an empty space." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == ".")
                {
                    cout << "It is an empty trail." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == "v")
                {
                    cout << "Alien finds an arrow and moves down." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto down;
                }
                else if (board[arp][acp] == "^")
                {
                    cout << "Alien finds an arrow and moves up." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto up;
                }
                else if (board[arp][acp] == "<")
                {
                    cout << "Alien finds an arrow and moves left." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto left;
                }
                else if (board[arp][acp] == ">")
                {
                    cout << "Alien finds an arrow and moves right." << endl;
                    cout << "Alien's attack is increased by 20." << endl;
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    if (alienAtk < 100)
                    {
                        alienAtk += 20;
                    }
                    else
                    {
                        alienAtk += 0;
                    }
                    system("cls");
                    printBoard(board, row, column);
                    disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
                    goto right;
                }
                else if (board[arp][acp] == "h")
                {
                    cout << "Alien finds a health pack." << endl;
                    if (alienLife < 100)
                    {
                        alienLife += 20;
                        cout << "Alien's life is increased by 20. (max life of Alien = 100)" << endl;
                        if (alienLife > 100)
                        {
                            alienLife = 100;
                        }
                    }
                    else
                    {
                        alienLife += 0;
                    }
                    system("PAUSE");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                    // bool alienLifeInc = true; // need check
                }
                else if (board[arp][acp] == "p")
                {
                    cout << "Alien finds a pod." << endl;
                    find_nearest_zomb(board, zomPos, numOfZombie, row, column, zrp, zcp, arp, acp, zombieLife);
                    // which nearest zombie kena damage?
                    /*if (zombieLife > 0)
                    {
                        cout << "Zombie [] is still alive" << endl;
                    }
                    else
                    {
                        cout << "Zombie [] is defeated." << endl;
                        zombie () position = " ";
                    }*/
                    system("pause");
                    board[arp][acp] = "A";
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == "r")
                {
                    cout << "Alien stumbles upon a rock." << endl;
                    int randnum = rand() % 11;
                    board[arp][acp] = objects[randnum];
                    cout << "Alien discovers a ' " << objects[randnum] << " ' beneath the rock." << endl;
                    system("pause");
                    arp--;
                    break;
                }
                else if (board[arp][acp] == "o")
                {
                    cout << "Alien finds a poison." << endl;
                    if (alienLife > 10)
                    {
                        alienLife -= 10;
                        cout << "Opps, Alien's life is decreased by 10." << endl;
                        board[arp][acp] = "A";
                    }
                    else
                    {
                        alienLife = 0;
                        cout << "Alien is defeated. Game Over" << endl;
                        board[arp][acp] = " ";
                        system("PAUSE");
                        restartPrompt2();
                        return;
                    }
                    system("PAUSE");
                    board[arpSave][acpSave] = ".";
                }
                else if (board[arp][acp] == "1")
                {
                    cout << "Alien meets zombie 1." << endl;
                    cout << "Zombie 1 receives a damage of " << alienAtk << endl;
                    zombieLife[0] -= alienAtk;
                    if (zombieLife[0] <= 0)
                    {
                        zombieLife[0] = 0;
                        cout << "Zombie 1 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "2")
                {
                    cout << "Alien meets zombie 2." << endl;
                    cout << "Zombie 2 receives a damage of " << alienAtk << endl;
                    zombieLife[1] -= alienAtk;
                    if (zombieLife[1] <= 0)
                    {
                        zombieLife[1] = 0;
                        cout << "Zombie 2 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "3")
                {
                    cout << "Alien meets zombie 3." << endl;
                    cout << "Zombie 3 receives a damage of " << alienAtk << endl;
                    zombieLife[2] -= alienAtk;
                    if (zombieLife[2] <= 0)
                    {
                        zombieLife[2] = 0;
                        cout << "Zombie 3 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "4")
                {
                    cout << "Alien meets zombie 4." << endl;
                    cout << "Zombie 4 receives a damage of " << alienAtk << endl;
                    zombieLife[3] -= alienAtk;
                    if (zombieLife[3] <= 0)
                    {
                        zombieLife[3] = 0;
                        cout << "Zombie 4 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "5")
                {
                    cout << "Alien meets zombie 5." << endl;
                    cout << "Zombie 5 receives a damage of " << alienAtk << endl;
                    zombieLife[4] -= alienAtk;
                    if (zombieLife[4] <= 0)
                    {
                        zombieLife[4] = 0;
                        cout << "Zombie 5 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "6")
                {
                    cout << "Alien meets zombie 6." << endl;
                    cout << "Zombie 6 receives a damage of " << alienAtk << endl;
                    zombieLife[5] -= alienAtk;
                    if (zombieLife[5] <= 0)
                    {
                        zombieLife[5] = 0;
                        cout << "Zombie 6 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "7")
                {
                    cout << "Alien meets zombie 7." << endl;
                    cout << "Zombie 7 receives a damage of " << alienAtk << endl;
                    zombieLife[6] -= alienAtk;
                    if (zombieLife[6] <= 0)
                    {
                        zombieLife[6] = 0;
                        cout << "Zombie 1 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "8")
                {
                    cout << "Alien meets zombie 8." << endl;
                    cout << "Zombie 8 receives a damage of " << alienAtk << endl;
                    zombieLife[7] -= alienAtk;
                    if (zombieLife[7] <= 0)
                    {
                        zombieLife[7] = 0;
                        cout << "Zombie 8 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp--;
                    bool alienAttackInc = true;
                    break;
                }
                else if (board[arp][acp] == "9")
                {
                    cout << "Alien meets zombie 9." << endl;
                    cout << "Zombie 9 receives a damage of " << alienAtk << endl;
                    zombieLife[8] -= alienAtk;
                    if (zombieLife[8] <= 0)
                    {
                        zombieLife[8] = 0;
                        cout << "Zombie 9 is defeated !" << endl;
                        board[arp][acp] = " ";
                    }
                    else
                    {
                    }
                    system("pause");
                    // board[arpSave][acpSave] = "A";
                    // board[arp][acp] = "1";
                    arp--;
                    bool alienAttackInc = true;
                    break;
                }
                else
                {
                    break;
                }
                system("cls");
                printBoard(board, row, column);
                disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
            }
        }
    }

    else
    {
        cout << "Invalid response." << endl;
        system("pause");
        system("cls");

        printBoard(board, row, column);
        disCharinfotype1(alienLife, alienAtk, numOfZombie, zombieLife, zombieAttack, zombieRange);
        cmd(board, totalZlife, numOfZombie, row, column, arp, acp, zrp, zcp, alienLife, alienAtk, zombieLife, zombieAttack, zombieRange, zomPos);
    }
}

void disCharinfotype1(int &alienLife, int &alienAtk, int numOfZombie, int *zombieLife, int *zombieAttack, int *zombieRange)
{
    cout << "->  Alien   : Life " << alienLife << " , Attack " << alienAtk << endl;

    for (int a = 0; a < numOfZombie; a++)
    {
        cout << "    Zombie " << a + 1 << ": Life " << zombieLife[a] << "  , Attack " << zombieAttack[a] << " , Range " << zombieRange[a] << endl;
    }
}

// zombie turn
void disCharinfotype2(int alienLife, int alienAtk, int numOfZombie, int *zombieLife, int *zombieAttack, int *zombieRange, int currentCount)
{
    cout << "    Alien   : Life " << alienLife << " , Attack " << alienAtk << endl;

    for (int a = 0; a < numOfZombie; a++)
    {
        if (a == currentCount && zombieLife[a] > 0)
        {
            cout << "->  Zombie " << a + 1 << ": Life " << zombieLife[a] << "  , Attack " << zombieAttack[a] << " , Range " << zombieRange[a] << endl;
        }
        else if (a != currentCount)
        {
            cout << "    Zombie " << a + 1 << ": Life " << zombieLife[a] << "  , Attack " << zombieAttack[a] << " , Range " << zombieRange[a] << endl;
        }
    }
}