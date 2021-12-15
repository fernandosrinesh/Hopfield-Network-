#include "HopfieldNetwork.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include<algorithm>
using namespace std;

vector<vector<int> > vec;
vector<int>InputVector, w, TestVector;
string output;

Hopfield::Hopfield()
{
    //ctor
}

Hopfield::~Hopfield()
{
    //dtor
}

/*This function is used to Store Input and Test Vectors obtained from User*/
void Hopfield::StoreInput(int ch, string line)
{
    switch (ch) {
    case 1:
    {
        // Parse the string and store in InputVector
        stringstream ss(line);
        for (int i; ss >> i;) {
            InputVector.push_back(i);
            if (ss.peek() == ',')
                ss.ignore();
        }
        break;
    }
    case 2:
    {
        // Parse the string and store in TestVector
        TestVector.clear();
        stringstream ss(line);
        for (int i; ss >> i;) {
            TestVector.push_back(i);
            if (ss.peek() == ',')
                ss.ignore();
        }
        break;
    }
    default:
        break;
    }
}

/*This function is used to Calculate the weight matrix for given Input Vectors*/
void Hopfield::CalculateWeightMatrix(int rows)
{
    int i, j, k, sum;
    int m = 1, n = 0;
    //Cycle length
    int cycle = 2;

    // No. of rows in training pattern
    m = rows;
    // Total No. of Neurons n is equal to no. of bits in 1 training pattern
    n = InputVector.size() / m;

    //Convert Inputvector to Bipolar
    std::replace(InputVector.begin(), InputVector.end(), 0, -1);

    // Calculate the weight matrix (symmetric and square)
    // w[i,j]=w[j,i] & i!=j (i==j => w=0)
    w.insert(w.begin(), n * n, 0);
    for (j = 0;j < n;j++) {
        for (i = j;i < n;i++) {
            if (i == j) {
                w[j * n + i] = 0;
            }
            else
            {
                sum = 0;
                for (k = 0;k < m;k++)
                {
                    sum += (InputVector[k * n + i]) * (InputVector[k * n + j]);
                }
                w[j * n + i] = sum;
                w[i * n + j] = sum;
            }
        }
    }
}

/*This function is used to Calculate HAM output with the given test pattern*/
void Hopfield::CalculateHAMOutput(int cycle,int rows)
{
    vector<int>neuron;      // current state of the network
    neuron = TestVector;
    std::replace(neuron.begin(), neuron.end(), 0, -1);
    // Initially prev state=current
    StoreOutput(neuron, cycle);
    int n = InputVector.size() / rows;
    int result = 0;
    int sum = 0;
    while (result == 0)
    {
        // Update all neurons simultaneously
        vector<int>neuron_temp(n, 0);
        for (int j = 0;j < n;j++)
        {
            sum = 0;
            for (int i = 0;i < n;i++)
            {
                if (i != j)
                    sum += neuron[i] * w[j * n + i];
                if (sum >= 0)
                    neuron_temp[j] = 1;
                else
                    neuron_temp[j] = -1;
            }
        }

        //Compare the new Output with all previous answers stored in vector size of cycle length.
        result = Compare(neuron_temp, cycle);
        //result is 0 if the new output does not match with any previous answers.
        if (result == 0)
        {
            // Update the previous network state
            StoreOutput(neuron_temp, cycle);
        }
        // update the neurons with the new values
        neuron.clear();// delete the old values
        neuron = neuron_temp; // update the array pointer
        
    }
    vec.clear();
}

/*This function is used to compare the new output with previous answers stored in a vector*/
int Hopfield::Compare(vector<int> V1, int cycle)
{
    output="";
    int temp_cycle = cycle-1;
    int temp_vecSize = vec.size();
    int retFlag = 0;
    for (int i = 0; i < temp_vecSize; i++)
    {
        if (vec[i] == V1)
        {
            //If the new output matches with previous answer the print the answer
            //In case if there is a cycle it will output both alternating answers
            if (i < (temp_cycle) && (temp_vecSize != 1))
            {
                output.append("There is a cycle of length 2");
                output.append("\n");
            }
            for(int k=i;k<vec.size();k++)
            {
            std::replace(vec[k].begin(), vec[k].end(), -1, 0);
            for(int j=0;j<vec[i].size();j++)
            { 
            output.append(to_string(vec[k][j]));
            output.append(" ");
            }
            output.append("\n");
            }
            retFlag=retFlag+1;
            break;
        }
    }
    return retFlag;
}

string Hopfield::GetOutput()
{ 
    return output;
}

/*This function is used to store previous answers*/
void Hopfield::StoreOutput(vector<int>val, int cycle)
{
    vector<vector<int> >::iterator it1;
    if (vec.size() == cycle)
    {
        it1 = vec.begin();
        vec.erase(it1);
    }
    vec.push_back(val);
}

/*Clear All Vectors*/
void Hopfield::ClearAll()
{
    InputVector.clear();
    TestVector.clear();
    output = "";
    w.clear();
    vec.clear();
}

/*Import Data From File*/
string Hopfield::GetInputFromFile()
{
    ifstream myfile;
    string InputString = "";
    int count = 0;

    myfile.open("Inputs.txt");
    if (myfile.is_open())
    {
        string line;
        while (getline(myfile, line))
        {
            StoreInput(1,line);
            InputString.append(line);
            InputString.append(";");
            count++;
        }
        myfile.close();
    }
    else
    {
        return "Unable to Open File";
    }
    InputString.pop_back();
    return InputString;
}


