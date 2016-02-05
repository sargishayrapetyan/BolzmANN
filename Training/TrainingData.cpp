#include "TrainingData.h"
#include <sstream>

using namespace ANN;

vector<int> TrainingData::getTopology()
{
    vector<int> topology;
    string      line;

    getline(trainingDataFile_, line);
    stringstream ss(line);

    string label;
    ss >> label;
    if (isEof() || label != "topology:") 
    {
        abort();
    }

    while (!ss.eof()) 
    {
        int n;
        ss >> n;
        topology.emplace_back(n);
    }

    return topology;
}

TrainingData::TrainingData(const string& filename)
{
    trainingDataFile_.open(filename.c_str());
}

int TrainingData::getNextInputs(vector<double>& inputVals)
{
    inputVals.clear();

    string line;
    getline(trainingDataFile_, line);
    stringstream ss(line);

    string label;
    ss >> label;
    if (label == "in:")
    {
        double oneValue;
        while (ss >> oneValue) 
        {
            inputVals.emplace_back(oneValue);
        }
    }

    return static_cast<int>(inputVals.size());
}

int TrainingData::getTargetOutputs(vector<double>& targetOutputVals)
{
    targetOutputVals.clear();

    string line;
    getline(trainingDataFile_, line);
    stringstream ss(line);

    string label;
    ss >> label;
    if (label == "out:")
    {
        double oneValue;
        while (ss >> oneValue) 
        {
            targetOutputVals.emplace_back(oneValue);
        }
    }

    return static_cast<int>(targetOutputVals.size());
}