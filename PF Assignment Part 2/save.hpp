#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <fstream>

#include <fstream>
#include <filesystem>

#include "struct.h"

namespace fs = std::filesystem;

using namespace std;

bool IsZombie(string val);
void savedim(string filename, int &row, int &column);
void saveFile(string filename, string **&board, int &row, int &column, int &arp, int &acp, int &numOfZombie, Position *&zomPos, int &alienLife, int &alienAtk, int *&zombieLife, int *&zombieAttack, int *&zombieRange);
void savedim(string filename, int &row, int &column);
void saveAlien(string filename, int &arp, int &acp);
void saveZombierp(string filename, Position *&zomPos, int &numOfZombie);
void saveZombiecp(string filename, Position *&zomPos, int &numOfZombie);
void ZomLife(string filename, int &numOfZombie, int *&zombieLife);
void ZomAtk(string filename, int &numOfZombie, int *&zombieAttack);
void ZomRange(string filename, int &numOfZombie, int *&zombieRange);
void AstatsAL(string filename, int &alienLife);
void AstatsAA(string filename, int &alienAtk);
void totalZ(string filename, int &numOfZombie);

bool IsZombie(string val)
{
    return val >= "1" && val <= "9";
}

void saveFile(string filename, string **&board, int &row, int &column, int &arp, int &acp, int &numOfZombie, Position *&zomPos, int &alienLife, int &alienAtk, int *&zombieLife, int *&zombieAttack, int *&zombieRange)
{
    fs::path folderPath = "./save";
    fs::path mainfilePath = folderPath / filename;

    if (!fs::exists(folderPath))
    {
        fs::create_directory(folderPath);
    }

    ofstream outFile(mainfilePath);
    if (!outFile)
    {
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (board[i][j] == " ")
            {
                board[i][j] = "*";
            }
        }
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            outFile << board[i][j] << " ";
        }

        outFile << endl;
    }

    string subfileDim = filename + "savedim";
    string subfileAlien = filename + "saveAlien";
    string subfileZombierp = filename + "saveZombierp";
    string subfileZombiecp = filename + "saveZombiecp";
    string subfileZomLife = filename + "ZomLife";
    string subfileZomAtk = filename + "ZomAtk";
    string subfileZomRange = filename + "ZomRange";
    string subfileAstatsAL = filename + "AstatsAL";
    string subfileAstatsAA = filename + "AstatsAA";
    string subfiletotalZ = filename + "totalZ";

    savedim(subfileDim, row, column);
    saveAlien(subfileAlien, arp, acp);
    saveZombierp(subfileZombierp, zomPos, numOfZombie);
    saveZombiecp(subfileZombiecp, zomPos, numOfZombie);
    ZomLife(subfileZomLife, numOfZombie, zombieLife);
    ZomAtk(subfileZomAtk, numOfZombie, zombieAttack);
    ZomRange(subfileZomRange, numOfZombie, zombieRange);
    AstatsAL(subfileAstatsAL, alienLife);
    AstatsAA(subfileAstatsAA, alienAtk);
    totalZ(subfiletotalZ, numOfZombie);


    outFile.close();
}

void savedim(string filename, int &row, int &column)
{
    fs::path folderPath = "./save";
    fs::path filePathDim = folderPath / filename;

    if (!fs::exists(folderPath))
    {
        fs::create_directory(folderPath);
    }

    ofstream outFile(filePathDim);
    if (!outFile)
    {
        return;
    }
    outFile << row << endl;
    outFile << column << endl;
    outFile.close();
}

void saveAlien(string filename, int &arp, int &acp)
{
    fs::path folderPath = "./save";
    fs::path filePathAlien = folderPath / filename;

    if (!fs::exists(folderPath))
    {
        fs::create_directory(folderPath);
    }

    ofstream outFile(filePathAlien);
    if (!outFile)
    {
        return;
    }
    outFile << arp << endl;
    outFile << acp << endl;
    outFile.close();
}

void saveZombierp(string filename, Position *&zomPos, int &numOfZombie)
{
    fs::path folderPath = "./save";
    fs::path filePathZom = folderPath / filename;

    if (!fs::exists(folderPath))
    {
        fs::create_directory(folderPath);
    }

    ofstream outFile(filePathZom);
    if (!outFile)
    {
        return;
    }

    for (int a = 0; a < numOfZombie; a++)
    {
        outFile << zomPos[a].rp << endl;
    }
    outFile.close();
}

void saveZombiecp(string filename, Position *&zomPos, int &numOfZombie)
{
    fs::path folderPath = "./save";
    fs::path filePathZom = folderPath / filename;

    if (!fs::exists(folderPath))
    {
        fs::create_directory(folderPath);
    }

    ofstream outFile(filePathZom);
    if (!outFile)
    {
        return;
    }

    for (int a = 0; a < numOfZombie; a++)
    {
        outFile << zomPos[a].cp << endl;
    }
    outFile.close();
}

void ZomLife(string filename, int &numOfZombie, int *&zombieLife)
{
    fs::path folderPath = "./save";
    fs::path filePathZom = folderPath / filename;

    if (!fs::exists(folderPath))
    {
        fs::create_directory(folderPath);
    }

    ofstream outFile(filePathZom);
    if (!outFile)
    {
        return;
    }

    for (int a = 0; a < numOfZombie; a++)
    {
        outFile << zombieLife[a] << endl;
    }
    outFile << 0 << endl;

    outFile.close();
}

void ZomAtk(string filename, int &numOfZombie, int *&zombieAttack)
{
    fs::path folderPath = "./save";
    fs::path filePathZom = folderPath / filename;

    if (!fs::exists(folderPath))
    {
        fs::create_directory(folderPath);
    }

    ofstream outFile(filePathZom);
    if (!outFile)
    {
        return;
    }

    for (int a = 0; a < numOfZombie; a++)
    {
        outFile << zombieAttack[a] << endl;
    }

    outFile.close();
}

void ZomRange(string filename, int &numOfZombie, int *&zombieRange)
{
    fs::path folderPath = "./save";
    fs::path filePathZom = folderPath / filename;

    if (!fs::exists(folderPath))
    {
        fs::create_directory(folderPath);
    }

    ofstream outFile(filePathZom);
    if (!outFile)
    {
        return;
    }

    for (int a = 0; a < numOfZombie; a++)
    {
        outFile << zombieRange[a] << endl;
    }

    outFile.close();
}

void AstatsAL(string filename, int &alienLife)
{
    fs::path folderPath = "./save";
    fs::path filePathZom = folderPath / filename;

    if (!fs::exists(folderPath))
    {
        fs::create_directory(folderPath);
    }

    ofstream outFile(filePathZom);
    if (!outFile)
    {
        return;
    }

    outFile << alienLife;

    outFile.close();
}

void AstatsAA(string filename, int &alienAtk)
{
    fs::path folderPath = "./save";
    fs::path filePathZom = folderPath / filename;

    if (!fs::exists(folderPath))
    {
        fs::create_directory(folderPath);
    }

    ofstream outFile(filePathZom);
    if (!outFile)
    {
        return;
    }

    outFile << alienAtk;

    outFile.close();
}

void totalZ(string filename, int &numOfZombie)
{
    fs::path folderPath = "./save";
    fs::path filePathZom = folderPath / filename;

    if (!fs::exists(folderPath))
    {
        fs::create_directory(folderPath);
    }

    ofstream outFile(filePathZom);
    if (!outFile)
    {
        return;
    }

    outFile << numOfZombie;

    outFile.close();
}