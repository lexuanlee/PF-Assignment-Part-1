#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <string>
#include "struct.h"


// #include "start.cpp"
// #include "func.cpp"
using namespace std;
// using namespace func;

//global
string objects[] = {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
                    "^", "^", "^", "^",  
                    "v", "v", "v", "v", 
                    "<", "<", "<", "<",  
                    ">", ">", ">", ">",  
                    "h", "h", "h", "h",  
                    "p", "p", "p",   
                    "o", "o",
                    "r", "r", "r", "r", "r"};
                    // 10 space
                    // 4 arrow each
                    // 4 health
                    // 3 pods
                    // 5 rocks
                    // 2 poison

                    // total = 40 w rocks
                    // total = 35 wt rocks


void printBoard(string **&board, int &row, int &column)
{

    for (int a = 0; a < column - 8; ++a)
    {
        cout << " ";
    }
    cout << ".: Alien vs Zombie :." << endl; // 21

    for (int i = 0; i < row; i++)
    {
        cout << "  ";
        for (int j = 0; j < column; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        cout << setw(2) << (i + 1);

        for (int j = 0; j < column; j++)
        {
            cout << "|" << board[i][j];
        }
        cout << "|" << endl;
    }
    cout << "  ";
    for (int j = 0; j < column; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;

    cout << "  ";
    for (int j = 0; j < column; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < column; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}
