#include "TrainingData.h"
#include "Net.h"
#include <iostream>
#include <cassert>

using namespace ANN;

void showsvectorVals(const std::string& label, const std::vector<double>& v)
{
    std::cout << label << " ";

    for (const auto& elem : v) 
    {
        std::cout << elem << " ";
    }

    std::cout << std::endl;
}

int main()
{
    TrainingData trainData("trainingData.txt");

    // e.g., { 3, 2, 1 }
    std::vector<int> topology;
    topology = trainData.getTopology();

    Net myNet(topology);

    std::vector<double> inputVals; 
    std::vector<double> targetVals;
    std::vector<double> resultVals;
    int            trainingPass = 0;
	int nTaguhi = 10;

    while (!trainData.isEof()) 
    {
        ++trainingPass;
        std::cout << std::endl << "Pass:    " << trainingPass << std::endl;

        // Get new input data and feed it forward:
        if (trainData.getNextInputs(inputVals) != topology[0]) 
        {
            break;
        }
        showsvectorVals("Inputs: ", inputVals);
        myNet.feedForward(inputVals);

        // Collect the net's actual output results:
        resultVals = myNet.getResults();
        showsvectorVals("Outputs:", resultVals);

        // Train the net what the outputs should have been:
        trainData.getTargetOutputs(targetVals);
        showsvectorVals("Targets:", targetVals);
        assert(targetVals.size() == topology.back());

        myNet.backProp(targetVals);

        // Report how well the training is working, average over recent samples:
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "Net recent average error: " << myNet.getRecentAverageError() << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }

    std::cout << std::endl << "Done" << std::endl;
}
