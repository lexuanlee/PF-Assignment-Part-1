// ******************************************************************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT8L
// Names: TEOH REN NEE | LEE LE XUAN | JACKTER UN CHIA TE
// IDs: 1221302069 | 1211102976 | 1211102020
// Emails: renneet88@gmail.com | lexuanxx0412@gmail.com | jackterun0420@gmail.com
// Phones: 016-7664907 | 016-7623545 | 013-5508970
// ******************************************************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include "help.hpp"
#include "save.hpp"
#include "load.hpp"
#include "condition.hpp"

using namespace std;

void defaultSetting();

int row = 5, column = 9, numOfZombie = 1;
int x, y;

void defaultSetting()
{
    string selection;
    cout << " " << endl;
    cout << "***********************" << endl;
    cout << "| Assignment (Part 1) |" << endl;
    cout << "|                     |" << endl;
    cout << "|  Let's Get Started! |" << endl;
    cout << "***********************" << endl;
    cout << " " << endl;
    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    : 5" << endl;
    cout << "Board Columns : 9" << endl;
    cout << "Zombie Count  : 1" << endl
         << endl;

    cout << "Do you wish to change the game settings (y/n)? => ";
    getline(cin >> ws, selection);
    while (selection != "y" && selection != "n")
    {
        cout << " " << endl;
        cout << "************************************************" << endl;
        cout << "|ATTENTION PLEASE! Only Accept Character (y/n) |" << endl;
        cout << "************************************************" << endl
             << endl;
        cout << "Do you wish to change the game settings (y/n)? => ";
        cin >> selection;
    }

    if (selection == "y")
    {
        system("Cls");
        cout << "Board Settings" << endl;
        cout << "------------------" << endl;
        cout << "Enter rows => ";
        cin >> row;
        while (row % 2 == 0 || cin.fail())
        {
            cin.clear();
            cin.ignore(200, '\n');
            cout << " " << endl;
            cout << "*******************************************" << endl;
            cout << "|ATTENTION PLEASE! Only accept odd number |" << endl;
            cout << "*******************************************" << endl
                 << endl;
            cout << "Enter rows => ";
            cin >> row;
        }
        cout << "Enter columns => ";
        cin >> column;

        while (column % 2 == 0 || cin.fail())
        {
            cin.clear();
            cin.ignore(200, '\n');
            cout << " " << endl;
            cout << "*******************************************" << endl;
            cout << "|ATTENTION PLEASE! Only accept odd number |" << endl;
            cout << "*******************************************" << endl
                 << endl;
            cout << "Enter Columns => ";
            cin >> column;
        }

        cout << endl;

        cout << "Zombie Settings" << endl;
        cout << "-------------------" << endl;
        cout << "Enter number of zombies => ";
        cin >> numOfZombie;
        while (numOfZombie > 9 || cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "*****************************************************************" << endl;
            cout << "|ATTENTION PLEASE! The number of zombies CANNOT be more than 9. |" << endl;
            cout << "*****************************************************************" << endl
                 << endl;
            cout << "Enter number of zombies => ";
            cin >> numOfZombie;
        }
        cout << endl;

        cout << "Settings updated." << endl;
        system("PAUSE");
    }
    else if (selection == "n")
    {
        cout << " " << endl;
        cout << "Default Settings Maintained. " << endl;
        row = 5;
        column = 9;
        numOfZombie = 1;
    }
}

class character
{
private:
    vector<vector<char>> board;

public:
    char alien = 'A';
    int alienLife = 100;
    int alienAttack = 0;
    char zombie = 'Z';
    int zomL = rand() % 5 + 1;
    int zomLife = zomL * 100;
    int zomAttack = rand() % 30 + 1;
    void game();
};

// fix the printed object
//  save and load file not working

void character::game()
{
    // initialize board
    character ch;
    char board[column][row];

    int x, y;

    char objects[] = {' ', ' ', ' ', ' ', ' ', '^', 'v', '<', '>', 'h', 'p', 'r', 'A', '.', '1', '2', '3', '4',
                      '5', '6', '7', '8', '9'};
    int noOfObjects = 12;
    int noOfObjectsNoRock = 11;

    for (x = 0; x < column; x++)
    {
        for (y = 0; y < row; y++)
        {
            int objNo = rand() % noOfObjects;
            board[x][y] = objects[objNo];
        }
        cout << endl;
    }

    for (int i = 14; i < numOfZombie + 14; i++)
    {
        int rc = rand() % column;
        int rr = rand() % row;

        // cout << rc << " " << rr << endl;
        // system("pause");
        board[rc][rr] = objects[i];
    }

    int mc = column / 2;
    int mr = row / 2;

    // cout << mc << " " << mr;

    board[mc][mr] = objects[12];

    int xpos = mc;
    int ypos = mr;

    // saving board for "reset"
    vector<vector<char>> boardHis;

    for (int i = 0; i < column; i++)
    {
        vector<char> rowHis;
        for (int j = 0; j < row; j++)
        {
            rowHis.push_back(board[i][j]);
        }
        boardHis.push_back(rowHis);
    }

    while (true)
    {
    refreshBoard:

        system("cls");

        board[xpos][ypos] = 'A';

        // cout << "refreshing board" << endl;

        // clear trail
        for (y = 0; y < row; y++)
        {
            for (x = 0; x < column; x++)
            {
                if (board[x][y] == '.')
                {
                    board[x][y] = ' ';
                }
            }
        }

        vector<vector<char>> boardVector;

        for (int i = 0; i < column; i++)
        {
            vector<char> rowVector;
            for (int j = 0; j < row; j++)
            {
                rowVector.push_back(board[i][j]);
            }
            boardVector.push_back(rowVector);
        }
        refresh(boardVector, column, row, numOfZombie);

    com:
        string command;

        cout << "Command: ";
        cin >> command;

        if (command == "quit")
        {
            exit(0);
        }
        // else if (command == "reset")
        // {
        //     refresh(boardHis, column, row, numOfZombie);
        //     goto refreshBoard;
        // }
        else if (command == "new")
        {
            ch.game();
        }
        else if (command == "arrow")
        {
            cout << "When you press enter, it goes to the next line." << endl;
            cout << "Command: column number" << endl;
            cout << "         row number" << endl;
            cout << "         arrow direction" << endl;

            system("pause");
            system("cls");

            refresh(boardVector, column, row, numOfZombie);

            int x, y;
            char arrow;
            cin >> x;
            cin >> y;
            cin >> arrow;

            if (arrow == 'v' || arrow == '^' || arrow == '<' || arrow == '>')
            {
                board[x - 1][y - 1] = arrow;
            }
            else
            {
                cout << "Invalid response." << endl;
                system("pause");
                system("cls");
                refresh(boardVector, column, row, numOfZombie);
                goto com;
            }

            vector<vector<char>> boardVector;

            for (int i = 0; i < column; i++)
            {
                vector<char> rowVector;
                for (int j = 0; j < row; j++)
                {
                    rowVector.push_back(board[i][j]);
                }
                boardVector.push_back(rowVector);
            }
            refresh(boardVector, column, row, numOfZombie);
            system("pause");
            goto refreshBoard;
        }
        else if (command == "help")
        {
            help();
            system("pause");
            goto refreshBoard;
        }
        else if (command == "save")
        {
            string filename;
            cout << "Enter the file name to save the current game (Eg: game1.txt): " << endl;
            cin >> filename;
            saveFile(filename, boardVector, row, column);
        }
        else if (command == "load")
        {
            string filename;
            cout << "Do you want to save the current game? (y/n): ";
            cin >> filename;
            loadFile(filename, boardVector, row, column);
        }

        else if (command == "left" || command == "right" || command == "up" || command == "down")
        {
            if (command == "left")
            {
            left:
                cout << "Alien move left." << endl;
                while (xpos > 0)
                {
                    system("pause");
                    int savex = xpos;
                    int savey = ypos;
                    board[savex][savey] = '.';

                    xpos--;

                    // repetitive can be shorten

                    if (board[xpos][ypos] >= '1' && board[xpos][ypos] <= '9')
                    {
                        stopcon(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        xpos = savex;
                        ypos = savey;
                        break;
                    }
                    else if (board[xpos][ypos] == 'r')
                    {
                        cout << "Alien hits rock" << endl;
                        system("PAUSE");
                        board[savex][savey] = 'A';
                        int objspawn = 11;
                        int randobj = rand() % objspawn;
                        board[xpos][ypos] = objects[randobj];
                        vector<vector<char>> boardVector;

                        for (int i = 0; i < column; i++)
                        {
                            vector<char> rowVector;
                            for (int j = 0; j < row; j++)
                            {
                                rowVector.push_back(board[i][j]);
                            }
                            boardVector.push_back(rowVector);
                        }
                        refresh(boardVector, column, row, numOfZombie);
                        system("pause");
                        xpos = savex;
                        ypos = savey;
                        break;
                    }
                    else if (board[xpos][ypos] == ' ' || board[xpos][ypos] == '.' || board[xpos][ypos] == 'h' || board[xpos][ypos] == 'p')
                    {
                        nonstopcon(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                    }
                    else if (board[xpos][ypos] == '^')
                    {
                        up(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto up;
                    }
                    else if (board[xpos][ypos] == 'v')
                    {
                        down(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto down;
                    }
                    else if (board[xpos][ypos] == '<')
                    {
                        left(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto left;
                    }
                    else if (board[xpos][ypos] == '>')
                    {
                        right(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto right;
                    }
                }
            }

            else if (command == "right")
            {
            right:
                cout << "Alien move right." << endl;
                while (xpos < column - 1)
                {
                    int savex = xpos;
                    int savey = ypos;
                    board[savex][savey] = '.';
                    xpos++;

                    if (board[xpos][ypos] >= '1' && board[xpos][ypos] <= '9')
                    {
                        stopcon(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        xpos = savex;
                        ypos = savey;
                        break;
                    }
                    else if (board[xpos][ypos] == 'r')
                    {
                        cout << "Alien hits rock" << endl;
                        system("PAUSE");
                        board[savex][savey] = 'A';
                        int objspawn = 11;
                        int randobj = rand() % objspawn;
                        board[xpos][ypos] = objects[randobj];
                        vector<vector<char>> boardVector;

                        for (int i = 0; i < column; i++)
                        {
                            vector<char> rowVector;
                            for (int j = 0; j < row; j++)
                            {
                                rowVector.push_back(board[i][j]);
                            }
                            boardVector.push_back(rowVector);
                        }
                        refresh(boardVector, column, row, numOfZombie);
                        system("pause");
                        xpos = savex;
                        ypos = savey;
                        break;
                    }
                    else if (board[xpos][ypos] == ' ' || board[xpos][ypos] == '.' || board[xpos][ypos] == 'h' || board[xpos][ypos] == 'p')
                    {
                        nonstopcon(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                    }
                    else if (board[xpos][ypos] == '^')
                    {
                        up(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto up;
                    }
                    else if (board[xpos][ypos] == 'v')
                    {
                        down(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto down;
                    }
                    else if (board[xpos][ypos] == '<')
                    {
                        left(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto left;
                    }
                    else if (board[xpos][ypos] == '>')
                    {
                        right(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto right;
                    }
                }
            }

            else if (command == "up")
            {
            up:
                cout << "Alien move up." << endl;
                while (ypos > 0)
                {
                    int savex = xpos;
                    int savey = ypos;
                    board[savex][savey] = '.';
                    ypos--;

                    if (board[xpos][ypos] >= '1' && board[xpos][ypos] <= '9')
                    {
                        stopcon(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        xpos = savex;
                        ypos = savey;
                        break;
                    }
                    else if (board[xpos][ypos] == 'r')
                    {
                        cout << "Alien hits rock" << endl;
                        system("PAUSE");
                        board[savex][savey] = 'A';
                        int objspawn = 11;
                        int randobj = rand() % objspawn;
                        board[xpos][ypos] = objects[randobj];
                        vector<vector<char>> boardVector;

                        for (int i = 0; i < column; i++)
                        {
                            vector<char> rowVector;
                            for (int j = 0; j < row; j++)
                            {
                                rowVector.push_back(board[i][j]);
                            }
                            boardVector.push_back(rowVector);
                        }
                        refresh(boardVector, column, row, numOfZombie);
                        system("pause");
                        xpos = savex;
                        ypos = savey;
                        break;
                    }
                    else if (board[xpos][ypos] == ' ' || board[xpos][ypos] == '.' || board[xpos][ypos] == 'h' || board[xpos][ypos] == 'p')
                    {
                        nonstopcon(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                    }
                    else if (board[xpos][ypos] == '^')
                    {
                        up(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto up;
                    }
                    else if (board[xpos][ypos] == 'v')
                    {
                        down(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto down;
                    }
                    else if (board[xpos][ypos] == '<')
                    {
                        left(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto left;
                    }
                    else if (board[xpos][ypos] == '>')
                    {
                        right(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto right;
                    }
                }
            }

            else if (command == "down")
            {

            down:
                cout << "Alien move down." << endl;
                while (ypos < row - 1)
                {
                    int savex = xpos;
                    int savey = ypos;
                    board[savex][savey] = '.';
                    ypos++;

                    if (board[xpos][ypos] >= '1' && board[xpos][ypos] <= '9')
                    {
                        stopcon(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        xpos = savex;
                        ypos = savey;
                        break;
                    }
                    else if (board[xpos][ypos] == 'r')
                    {
                        cout << "Alien hits rock" << endl;
                        system("PAUSE");
                        board[savex][savey] = 'A';
                        int objspawn = 11;
                        int randobj = rand() % objspawn;
                        board[xpos][ypos] = objects[randobj];
                        vector<vector<char>> boardVector;

                        for (int i = 0; i < column; i++)
                        {
                            vector<char> rowVector;
                            for (int j = 0; j < row; j++)
                            {
                                rowVector.push_back(board[i][j]);
                            }
                            boardVector.push_back(rowVector);
                        }
                        refresh(boardVector, column, row, numOfZombie);
                        system("pause");
                        xpos = savex;
                        ypos = savey;
                        break;
                    }
                    else if (board[xpos][ypos] == ' ' || board[xpos][ypos] == '.' || board[xpos][ypos] == 'h' || board[xpos][ypos] == 'p')
                    {
                        nonstopcon(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                    }
                    else if (board[xpos][ypos] == '^')
                    {
                        up(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto up;
                    }
                    else if (board[xpos][ypos] == 'v')
                    {
                        down(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto down;
                    }
                    else if (board[xpos][ypos] == '<')
                    {
                        left(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto left;
                    }
                    else if (board[xpos][ypos] == '>')
                    {
                        right(numOfZombie, column, row, xpos, ypos, savex, savey, boardVector);
                        goto right;
                    }
                }
            }
        }

        else
        {
            cout << "Invalid Response" << endl;
            system("pause");
            system("cls");
            refresh(boardVector, column, row, numOfZombie);
            goto com;
        }
        cout << "Alien turn end. The trail resets" << endl;
        system("pause");
        board[xpos][ypos] = 'A';
        goto refreshBoard;
    }
}

int main()
{
    srand(time(NULL));

    defaultSetting();

    character ch;

    // turn
    while (true)
    {
        ch.game();

        for (int count = 1; count <= numOfZombie; count++)
        {
            cout << "Zombie " << count << "'s turn." << endl;
            // ch.zombie()
        }
    }
exit:
    abort;
}
