#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <fstream>
using namespace std;

void saveFile(string filename, vector<vector<char>> &boardsave, int row, int column)
{

    ofstream file(filename);
    if (file.is_open())
    {
        for (int x = 0; x < row; x++)
        {
            for (int y = 0; y < column; y++)
            {
                file << boardsave[x][y];
            }
            file << endl;
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}