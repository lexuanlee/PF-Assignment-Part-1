#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include "struct.h"

#include <fstream>
#include <filesystem>

using namespace std;

namespace fs = filesystem;

void loadFile(bool &unableOpen, string filename, string **&board, int &row, int &column, int &arp, int &acp, int &numOfZombie, Position *&zomPos, int &alienLife, int &alienAtk, int *&zombieLife, int *&zombieAttack, int *&zombieRange);
void loaddim(string filename, int &row, int &column);
void loadAlien(string filename, int &arp, int &acp);
void loadZomrp(string filename, Position *&zomPos, int &numOfZombie);
void loadZomcp(string filename, Position *&zomPos, int &numOfZombie);
void loadAstatsAL(string filename, int &alienLife);
void loadAstatsAA(string filename, int &alienAtk);
void loadZomLife(string filename, int &numOfZombie, int *&zombieLife);
void loadZomAtk(string filename, int &numOfZombie, int *&zombieAttack);
void loadZomRange(string filename, int &numOfZombie, int *&zombieRange);
void loadtotalZ(string filename, int &numOfZombie);

void loadFile(bool &unableOpen, string filename, string **&board, int &row, int &column, int &arp, int &acp, int &numOfZombie, Position *&zomPos, int &alienLife, int &alienAtk, int *&zombieLife, int *&zombieAttack, int *&zombieRange)
{
    fs::path folderPath = "./save";
    fs::path mainfilePath = folderPath / filename;

    ifstream inFile(mainfilePath);
    if (!inFile)
    {
        unableOpen = true;
        return;
    }

    string subfileDim = filename + "savedim";
    fs::path subfilePath = folderPath / subfileDim;

    int inputRow, inputColumn;
    ifstream dimFile(subfilePath);
    dimFile >> inputRow >> inputColumn;

    // cout << inputRow << inputColumn << endl << row << column << endl;
    // system("pause");

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            board[i][j] = " ";
        }
    }

    string subfileAlien = filename + "saveAlien";
    string subfileZombierp = filename + "saveZombierp";
    string subfileZombiecp = filename + "saveZombiecp";
    string subfileZomLife = filename + "ZomLife";
    string subfileZomAtk = filename + "ZomAtk";
    string subfileZomRange = filename + "ZomRange";
    string subfileAstatsAL = filename + "AstatsAL";
    string subfileAstatsAA = filename + "AstatsAA";
    string subfiletotalZ = filename + "totalZ";

    loaddim(subfileDim, row, column);
    loadAlien(subfileAlien, arp, acp);
    loadZomrp(subfileZombierp, zomPos, numOfZombie);
    loadZomcp(subfileZombiecp, zomPos, numOfZombie);
    loadAstatsAL(subfileAstatsAL, alienLife);
    loadAstatsAA(subfileAstatsAA, alienAtk);
    loadZomLife(subfileZomLife, numOfZombie, zombieLife);
    loadZomAtk(subfileZomAtk, numOfZombie, zombieAttack);
    loadZomRange(subfileZomRange, numOfZombie, zombieRange);
    loadtotalZ(subfiletotalZ, numOfZombie);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            inFile >> board[i][j];
        }
    }

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
    inFile.close();
    // cout << alienLife << " " << alienAtk << endl;
    // for (int a = 0; a < numOfZombie; a++)
    // {
    //     cout << zombieLife[a] << " " << zombieAttack[a] << " " << zombieRange[a] << endl;
    // }
    // system("pause");
    // return alienLife, alienAtk, zombieAttack, zombieLife, zombieRange;
}

void loaddim(string filename, int &row, int &column)
{
    fs::path folderPath = "./save";
    fs::path subfilePath = folderPath / filename;

    ifstream inFile(subfilePath);
    if (!inFile)
    {
        return;
    }

    inFile >> row;
    inFile >> column;
    inFile.close();
}

void loadAlien(string filename, int &arp, int &acp)
{
    fs::path folderPath = "./save";
    fs::path subfilePath = folderPath / filename;

    ifstream inFile(subfilePath);
    if (!inFile)
    {
        return;
    }

    inFile >> arp;
    inFile >> acp;
    inFile.close();
    return;
}

void loadZomrp(string filename, Position *&zomPos, int &numOfZombie)
{
    fs::path folderPath = "./save";
    fs::path subfilePath = folderPath / filename;

    ifstream inFile(subfilePath);
    if (!inFile)
    {
        return;
    }

    for (int a = 0; a < numOfZombie; a++)
    {
        inFile >> zomPos[a].rp;
    }
    inFile.close();
    return;
}

void loadZomcp(string filename, Position *&zomPos, int &numOfZombie)
{
    fs::path folderPath = "./save";
    fs::path subfilePath = folderPath / filename;

    ifstream inFile(subfilePath);
    if (!inFile)
    {
        return;
    }

    for (int a = 0; a < numOfZombie; a++)
    {
        inFile >> zomPos[a].cp;
    }
    inFile.close();
    return;
}

void loadAstatsAL(string filename, int &alienLife)
{
    fs::path folderPath = "./save";
    fs::path subfilePath = folderPath / filename;

    ifstream inFile(subfilePath);
    if (!inFile)
    {
        return;
    }

    inFile >> alienLife;
    inFile.close();
}

void loadAstatsAA(string filename, int &alienAtk)
{
    fs::path folderPath = "./save";
    fs::path subfilePath = folderPath / filename;

    ifstream inFile(subfilePath);
    if (!inFile)
    {
        return;
    }

    inFile >> alienAtk;
    inFile.close();
    return;
}

void loadZomLife(string filename, int &numOfZombie, int *&zombieLife)
{
    fs::path folderPath = "./save";
    fs::path subfilePath = folderPath / filename;

    ifstream inFile(subfilePath);
    if (!inFile)
    {
        return;
    }
    for (int a = 0; a < numOfZombie; a++)
    {
        inFile >> zombieLife[a];
    }
    cout << endl;
    inFile.close();
    return;
}

void loadZomAtk(string filename, int &numOfZombie, int *&zombieAttack)
{
    fs::path folderPath = "./save";
    fs::path subfilePath = folderPath / filename;

    ifstream inFile(subfilePath);
    if (!inFile)
    {
        return;
    }

    for (int a = 0; a < numOfZombie; a++)
    {
        inFile >> zombieAttack[a];
    }
    cout << endl;
    inFile.close();
    return;
}

void loadZomRange(string filename, int &numOfZombie, int *&zombieRange)
{
    fs::path folderPath = "./save";
    fs::path subfilePath = folderPath / filename;

    ifstream inFile(subfilePath);
    if (!inFile)
    {
        return;
    }

    for (int a = 0; a < numOfZombie; a++)
    {
        inFile >> zombieRange[a];
    }
    cout << endl;
    inFile.close();
    return;
}

void loadtotalZ(string filename, int &numOfZombie)
{
    fs::path folderPath = "./save";
    fs::path subfilePath = folderPath / filename;

    ifstream inFile(subfilePath);
    if (!inFile)
    {
        return;
    }

    inFile >> numOfZombie;

    inFile.close();
    return;
}