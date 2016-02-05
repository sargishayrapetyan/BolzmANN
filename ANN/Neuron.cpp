#include "Neuron.h"

using namespace ANN;

double Neuron::eta   = 0.15;  // overall net learning rate, [0.0..1.0]
double Neuron::alpha = 0.5;   // momentum, multiplier of last deltaWeight, [0.0..1.0]

void Neuron::updateInputWeights(Layer& prevLayer)
{
    // The weights to be updated are in the Connection container
    // in the neurons in the preceding layer

    for (auto& neuron : prevLayer)
    {
        double oldDeltaWeight = neuron.outputWeights_[myIndex_].deltaWeight;
        double newDeltaWeight =
            // Individual input, magnified by the gradient and train rate:
            eta * neuron.getOutputVal() * gradient_
            // Also add momentum = a fraction of the previous delta weight;
            + alpha * oldDeltaWeight;

        neuron.outputWeights_[myIndex_].deltaWeight = newDeltaWeight;
        neuron.outputWeights_[myIndex_].weight     += newDeltaWeight;
    }
}

double Neuron::sumDOW(const Layer& nextLayer) const
{
    double sum = 0.0;

    // Sum our contributions of the errors at the nodes we feed.

    for (int n = 0; n < nextLayer.size() - 1; ++n)
    {
        sum += outputWeights_[n].weight * nextLayer[n].gradient_;
    }

    return sum;
}

void Neuron::calcHiddenGradients(const Layer& nextLayer)
{
    double dow = sumDOW(nextLayer);
    gradient_  = dow * Neuron::transferFunctionDerivative(outputVal_);
}

void Neuron::calcOutputGradients(const double targetVal)
{
    double delta = targetVal - outputVal_;
    gradient_    = delta * Neuron::transferFunctionDerivative(outputVal_);
}

double Neuron::transferFunction(const double x)
{
    // tanh - output range [-1.0..1.0]

    return tanh(x);
}

double Neuron::transferFunctionDerivative(const double x)
{
    // tanh derivative
    return 1.0 - x * x;
}

void Neuron::feedForward(const Layer& prevLayer)
{
    double sum = 0.0;

    // Sum the previous layer's outputs (which are our inputs)
    // Include the bias node from the previous layer.

    for (const auto& neuron : prevLayer) 
    {
        sum += neuron.getOutputVal() *
               neuron.outputWeights_[myIndex_].weight;
    }

    outputVal_ = Neuron::transferFunction(sum);
}

Neuron::Neuron(int numOutputs, int myIndex) : outputVal_(0.0), gradient_(0.0)
{
    for (int c = 0; c < numOutputs; ++c)
    {
        outputWeights_.emplace_back(Connection());
        outputWeights_.back().weight = randomWeight();
    }

    myIndex_ = myIndex;
}
