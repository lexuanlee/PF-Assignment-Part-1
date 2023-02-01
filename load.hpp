#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <fstream>
using namespace std;

void loadFile(string filename, vector<vector<char>> &boardload, int row, int column)
{
    ifstream file(filename);
    if (file.is_open())
    {
        for (int x = 0; x < row; x++)
        {
            for (int y = 0; y < column; y++)
            {
                file >> boardload[x][y];
            }
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file";
        system("pause");
    }
}