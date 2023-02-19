#include <iostream>
using namespace std;

void defaultSetting();
string tracker;
int row = 5, column = 9, numOfZombie = 1;
int x, y;

void defaultSetting()
{
    string selection;
    cout << " " << endl;
    cout << "***********************" << endl;
    cout << "| Assignment (Part 2) |" << endl;
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
        while (row % 2 == 0 || cin.fail() || row < 5 || row > 89)
        {
            cin.clear();
            cin.ignore(89, '\n');
            cout << " " << endl;
            cout << "************************************************************" << endl;
            cout << "|ATTENTION PLEASE! Only accept odd number between 5 and 89.|" << endl;
            cout << "************************************************************" << endl
                 << endl;
            cout << "Enter rows => ";
            cin >> row;
        }
        cout << "Enter columns => ";
        cin >> column;

        while (column % 2 == 0 || cin.fail() || column < 5 || column > 89)
        {
            cin.clear();
            cin.ignore(89, '\n');
            cout << " " << endl;
            cout << "************************************************************" << endl;
            cout << "|ATTENTION PLEASE! Only accept odd number between 5 and 89.|" << endl;
            cout << "************************************************************" << endl
                 << endl;
            cout << "Enter Columns => ";
            cin >> column;
        }

        cout << endl;

        cout << "Zombie Settings" << endl;
        cout << "-------------------" << endl;
        cout << "*************************************************************************" << endl;
        cout << "*  Note to User from Dev Team:                                          *" << endl;
        cout << "*  We recommend that the number of zombies set follow these perimeters  *" << endl;
        cout << "*  For 5 x 5, number of zombies is at most 3.                           *" << endl;
        cout << "*  For 7 x 7, number of zombies is at most 5.                           *" << endl;
        cout << "*  This is to avoid jeopardizing your User Experience. Have Fun!        *" << endl;
        cout << "*  However, the Dev Team would like to give Users the freedom to choose.*" << endl;
        cout << "*  Have Fun!                                                            *" << endl;
        cout << "*************************************************************************" << endl
             << endl;
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
        cout << "Do you wish to enable tracker for zombie (y/n)? => ";
        cin >> tracker;
        if (tracker == "y")
        {
            string y = to_string(1);
        }
        else if (tracker == "n")
        {
            string n = to_string(0);
        }
        else
        {
            cout << "Invalid response. Please enter only (y / n)" << endl
                 << endl;
            cout << "Do you wish to enable tracker for zombie (y/n)? => ";
            cin >> tracker;
            if (tracker == "y")
            {
                string y = to_string(1);
            }
            else
            {
                string n = to_string(0);
            }
        }
        cout << "Settings updated." << endl;
        system("PAUSE");
    }
    else if (selection == "n")
    {
        // string tracker;
        cout << "Do you wish to enable tracker for zombie (y/n)? => ";
        cin >> tracker;
        if (tracker == "y")
        {
            string y = to_string(1);
        }
        else if (tracker == "n")
        {
            string n = to_string(0);
        }
        else
        {
            cout << "Invalid response. Please enter only (y / n)" << endl
                 << endl;
            cout << "Do you wish to enable tracker for zombie (y/n)? => ";
            cin >> tracker;
            if (tracker == "y")
            {
                string y = to_string(1);
            }
            else
            {
                string n = to_string(0);
            }
        }
        cout << "Settings updated." << endl;
        system("PAUSE");
        cout << "Default Settings Maintained. " << endl;
        row = 5;
        column = 9;
        numOfZombie = 1;
    }
}
