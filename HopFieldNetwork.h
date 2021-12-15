#ifndef HOPFIELD_H
#define HOPFIELD_H

#include <string>
#include<vector>
using namespace std;

class Hopfield
{
public:
    Hopfield();
    virtual ~Hopfield();
    void StoreInput(int ch, string line);
    void CalculateWeightMatrix(int rows);
    void StoreOutput(vector<int>val, int cycle);
    void CalculateHAMOutput(int cycle, int rows);
    int Compare(vector<int> V1, int cycle);
    string GetInputFromFile();
    string GetOutput();
    void ClearAll();

protected:

private:
};

#endif // HOPFIELD_H
