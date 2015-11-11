#pragma once
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class TrainingData
{
public:
    TrainingData(const string filename);
    bool isEof(void) { return m_trainingDataFile.eof(); }
    void getTopology(vector<int> &topology);

    // Returns the number of input values read from the file:
    int getNextInputs(vector<double> &inputVals);
    int getTargetOutputs(vector<double> &targetOutputVals);

private:
    ifstream m_trainingDataFile;
};
