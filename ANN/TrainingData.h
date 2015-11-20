#ifndef TRAININGDATA_H
#define TRAININGDATA_H

#include <vector>
#include <fstream>
#include <string>

using namespace std;
namespace ANN
{
	class TrainingData
	{
	public:
		TrainingData(const string filename);
		bool isEof() { return trainingDataFile_.eof(); }
		void getTopology(vector<int>& topology);

		// Returns the number of input values read from the file:
		int getNextInputs(vector<double>& inputVals);
		int getTargetOutputs(vector<double>& targetOutputVals);

	private:
		ifstream trainingDataFile_;
	};
}
#endif // TRAININGDATA_H
