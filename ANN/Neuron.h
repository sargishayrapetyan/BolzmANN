#ifndef NEURON_H
#define NEURON_H

#include <vector>

using namespace std;
namespace ANN
{
	struct Connection
	{
		double weight;
		double deltaWeight;
	};

	class Neuron;
	typedef vector<Neuron> Layer;

	class Neuron
	{
	public:
		Neuron(int numOutputs, int myIndex);
		void   setOutputVal(double val) { outputVal_ = val; }
		double getOutputVal() const { return outputVal_; }
		void   feedForward(const Layer& prevLayer);
		void   calcOutputGradients(double targetVal);
		void   calcHiddenGradients(const Layer& nextLayer);
		void   updateInputWeights(const Layer& prevLayer);

	private:
		static double eta;   // [0.0..1.0] overall net training rate
		static double alpha; // [0.0..n] multiplier of last weight change (momentum)
		static double transferFunction(double x);
		static double transferFunctionDerivative(double x);
		static double randomWeight() { return rand() / double(RAND_MAX); }
		double sumDOW(const Layer& nextLayer) const;
		double             outputVal_;
		vector<Connection> outputWeights_;
		int                myIndex_;
		double             gradient_;
	};
}
#endif // NEURON_H
