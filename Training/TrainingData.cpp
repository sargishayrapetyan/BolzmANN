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
    if (this->isEof() || label.compare("topology:") != 0) {
        abort();
    }

    while (!ss.eof()) {
        int n;
        ss >> n;
        topology.push_back(n);
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
    if (label.compare("in:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            inputVals.push_back(oneValue);
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
    if (label.compare("out:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            targetOutputVals.push_back(oneValue);
        }
    }

    return static_cast<int>(targetOutputVals.size());
}