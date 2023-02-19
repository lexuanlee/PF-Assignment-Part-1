#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// global
string movesets[] = {"1", "2", "3", "4"};

// Any changes only do in InvalidSpace and ValidSpace
bool InvalidSpace(string val)
{
    return val >= "1" && val <= "9" || val == "A" || val == "r";
}

bool ValidSpace(string val)
{
    return val == " " || val == "h" || val == "p" || val == ">" || val == "<" || val == "v" || val == "^";
}

bool RightValid(int zrp, int zcp, int column, string **board)
{
    return zcp != (column - 1) || ValidSpace(board[zrp][zcp + 1]);
}

bool LeftValid(int zrp, int zcp, string **board)
{
    return zcp != 0 || ValidSpace(board[zrp][zcp - 1]);
}

bool UpValid(int zrp, int zcp, string **board)
{
    return zrp != 0 || ValidSpace(board[zrp - 1][zcp]);
}

bool DownValid(int zrp, int zcp, int row, string **board)
{
    return zrp != (row - 1) || ValidSpace(board[zrp + 1][zcp]);
}

bool RightInvalid(int zrp, int zcp, int column, string **board)
{
    return zcp == (column - 1) || InvalidSpace(board[zrp][zcp + 1]);
}

bool LeftInvalid(int zrp, int zcp, string **board)
{
    return zcp == 0 || InvalidSpace(board[zrp][zcp - 1]);
}

bool UpInvalid(int zrp, int zcp, string **board)
{
    return zrp == 0 || InvalidSpace(board[zrp - 1][zcp]);
}

bool DownInvalid(int zrp, int zcp, int row, string **board)
{
    return zrp == (row - 1) || InvalidSpace(board[zrp + 1][zcp]);
}

void trackerOff(int &zrp, int &zcp, int &row, int &column, string **board, string &randmove)
{

    // Surrounded 4 corner
    // Surrounded 3 corner
    // Surrounded 2 corner - neighbour corner / up down / left right
    // Surrounded 1 corner
    // Not surrounded

    if (LeftInvalid(zrp, zcp, board) && RightInvalid(zrp, zcp, column, board) && UpInvalid(zrp, zcp, board) && DownInvalid(zrp, zcp, row, board))
    {
        cout << "Zombie could not move" << endl;
    }

    else if (RightInvalid(zrp, zcp, column, board) && UpInvalid(zrp, zcp, board) && DownInvalid(zrp, zcp, row, board))
    {
        randmove = "1";
    }

    else if (LeftInvalid(zrp, zcp, board) && UpInvalid(zrp, zcp, board) && DownInvalid(zrp, zcp, row, board))
    {
        randmove = "2";
    }

    else if (LeftInvalid(zrp, zcp, board) && RightInvalid(zrp, zcp, column, board) && DownInvalid(zrp, zcp, row, board))
    {
        randmove = "3";
    }

    else if (LeftInvalid(zrp, zcp, board) && RightInvalid(zrp, zcp, column, board) && UpInvalid(zrp, zcp, board))
    {
        randmove = "4";
    }

    else if (RightInvalid(zrp, zcp, column, board) && UpInvalid(zrp, zcp, board))
    {
        while (true)
        {
            randmove = movesets[rand() % 4];

            if (randmove != "2" && randmove != "3")
            {
                // cout << randmove << endl;
                // system("pause");
                break;
            }
        }
    }

    else if (LeftInvalid(zrp, zcp, board) && UpInvalid(zrp, zcp, board))
    {
        while (true)
        {
            randmove = movesets[rand() % 4];

            if (randmove != "1" && randmove != "3")
            {
                // cout << randmove << endl;
                // system("pause");
                break;
            }
        }
    }

    else if (RightInvalid(zrp, zcp, column, board) && DownInvalid(zrp, zcp, row, board))
    {
        while (true)
        {
            randmove = movesets[rand() % 4];

            if (randmove != "2" && randmove != "4")
            {
                // cout << randmove << endl;
                // system("pause");
                break;
            }
        }
    }

    else if (LeftInvalid(zrp, zcp, board) && DownInvalid(zrp, zcp, row, board))
    {
        while (true)
        {
            randmove = movesets[rand() % 4];

            if (randmove != "1" && randmove != "4")
            {
                // cout << randmove << endl;
                // system("pause");
                break;
            }
        }
    }

    else if (LeftInvalid(zrp, zcp, board) && RightInvalid(zrp, zcp, column, board))
    {
        while (true)
        {
            randmove = movesets[rand() % 4];

            if (randmove != "1" && randmove != "2")
            {
                // cout << randmove << endl;
                // system("pause");
                break;
            }
        }
    }

    else if (UpInvalid(zrp, zcp, board) && DownInvalid(zrp, zcp, row, board))
    {
        while (true)
        {
            randmove = movesets[rand() % 4];

            if (randmove != "3" && randmove != "4")
            {
                // cout << randmove << endl;
                // system("pause");
                break;
            }
        }
    }

    else if (LeftInvalid(zrp, zcp, board))
    {
        // cout << "option1" << endl;
        while (true)
        {
            randmove = movesets[rand() % 4];
            // cout << randmove << endl;
            if (randmove != "1")
            {
                // cout << randmove << endl;
                // system("pause");
                break;
            }
        }
    }
    else if (RightInvalid(zrp, zcp, column, board))
    {
        // cout << "option2" << endl;
        while (true)
        {
            randmove = movesets[rand() % 4];
            // cout << randmove << endl;
            if (randmove != "2")
            {
                // cout << randmove << endl;
                // system("pause");
                break;
            }
        }
    }
    else if (UpInvalid(zrp, zcp, board))
    {
        // cout << "option3" << endl;
        while (true)
        {
            randmove = movesets[rand() % 4];
            // cout << randmove << endl;
            if (randmove != "3")
            {
                // cout << randmove << endl;
                // system("pause");
                break;
            }
        }
    }
    else if (DownInvalid(zrp, zcp, row, board))
    {
        // cout << "option4" << endl;
        while (true)
        {
            randmove = movesets[rand() % 4];
            // cout << randmove << endl;
            if (randmove != "4")
            {
                // cout << randmove << endl;
                // system("pause");
                break;
            }
        }
    }
    else
    {
        randmove = movesets[rand() % 4];
        // cout << randmove << endl;
        // system("pause");
    }
}

void trackerOn(int &zrp, int &zcp, int &arp, int &acp, int &row, int &column, string **board, string &randmove)
{

    // 1 - left
    // 2 - right
    // 3 - up
    // 4 - down
    // tracker is specified conditions

    // cout << zrp << " " << zcp << endl;
    // cout << arp << " " << acp << endl;

    string randmoveTracker;
    string trcmovesets[] = {"1", "2"};
    int diffRow = abs(arp - zrp);
    int diffCol = abs(acp - zcp);
    if (diffRow < diffCol)
    {
        // cout << "opt1" << endl;
        // system("pause");
        randmoveTracker = "2";
    }
    else if (diffCol < diffRow)
    {
        // cout << "opt2" << endl;
        // system("pause");
        randmoveTracker = "1";
    }
    else
    {
        randmoveTracker = trcmovesets[rand() % 2];
    }

    // cout << randmoveTracker << endl;

    // cout << diffRow << " " << diffCol << endl;

    // special tracker condition
    if (zcp == acp && arp < zrp && UpValid(zrp, zcp, board))
    {
        // cout << "opt3" << endl;
        // system("pause");
        randmove = "3";
    }
    else if (zcp == acp && zrp < arp && DownValid(zrp, zcp, row, board))
    {
        // cout << "opt4" << endl;
        // system("pause");
        randmove = "4";
    }
    else if (zrp == arp && acp < zcp && LeftValid(zrp, zcp, board))
    {
        // cout << "opt5" << endl;
        // system("pause");
        randmove = "1";
    }
    else if (zrp == arp && zcp < acp && RightValid(zrp, zcp, column, board))
    {
        // cout << "opt6" << endl;
        // system("pause");
        randmove = "2";
    }

    // zombie will move left or right
    else if (randmoveTracker == "1" && zcp < acp && RightValid(zrp, zcp, column, board))
    {
        // zombie will move to the right
        // cout << "opt7" << endl;
        // system("pause");
        randmove = "2";
    }
    else if (randmoveTracker == "1" && acp < zcp && LeftValid(zrp, zcp, board))
    {
        // zombie will move to the left
        // cout << "opt8" << endl;
        // system("pause");
        randmove = "1";
    }

    // zombie will move up or down
    else if (randmoveTracker == "2" && zrp < arp && DownValid(zrp, zcp, row, board))
    {
        // zombie will move to the down
        // cout << "opt9" << endl;
        // system("pause");
        randmove = "4";
    }
    else if (randmoveTracker == "2" && arp < zrp && UpValid(zrp, zcp, board))
    {
        // zombie will move to the up
        // cout << "opt10" << endl;
        // system("pause");
        randmove = "3";
    }

    // if none the above tracker condition met, standard movements will be executed.
    else
    {
        // cout << "opt11" << endl;
        // system("pause");
        trackerOff(zrp, zcp, row, column, board, randmove);
    }
}

void moveIndic(string randmove)
{
    if (randmove == "1")
    {
        cout << "Zombie move left." << endl;
    }
    else if (randmove == "2")
    {
        cout << "Zombie move right." << endl;
    }
    else if (randmove == "3")
    {
        cout << "Zombie move up." << endl;
    }
    else if (randmove == "4")
    {
        cout << "Zombie move down." << endl;
    }
}