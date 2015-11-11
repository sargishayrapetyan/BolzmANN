#include "Neuron.h"

double Neuron::eta = 0.15;    // overall net learning rate, [0.0..1.0]
double Neuron::alpha = 0.5;   // momentum, multiplier of last deltaWeight, [0.0..1.0]

void Neuron::updateInputWeights(Layer &prevLayer)
{
    // The weights to be updated are in the Connection container
    // in the neurons in the preceding layer

    for (int n = 0; n < prevLayer.size(); ++n) {
        Neuron &neuron = prevLayer[n];
        double oldDeltaWeight = neuron.outputWeights_[myIndex_].deltaWeight;

        double newDeltaWeight =
            // Individual input, magnified by the gradient and train rate:
            eta
            * neuron.getOutputVal()
            * gradient_
            // Also add momentum = a fraction of the previous delta weight;
            + alpha
            * oldDeltaWeight;

        neuron.outputWeights_[myIndex_].deltaWeight = newDeltaWeight;
        neuron.outputWeights_[myIndex_].weight += newDeltaWeight;
    }
}

double Neuron::sumDOW(const Layer &nextLayer) const
{
    double sum = 0.0;

    // Sum our contributions of the errors at the nodes we feed.

    for (int n = 0; n < nextLayer.size() - 1; ++n) {
        sum += outputWeights_[n].weight * nextLayer[n].gradient_;
    }

    return sum;
}

void Neuron::calcHiddenGradients(const Layer &nextLayer)
{
    double dow = sumDOW(nextLayer);
    gradient_ = dow * Neuron::transferFunctionDerivative(outputVal_);
}

void Neuron::calcOutputGradients(double targetVal)
{
    double delta = targetVal - outputVal_;
    gradient_ = delta * Neuron::transferFunctionDerivative(outputVal_);
}

double Neuron::transferFunction(double x)
{
    // tanh - output range [-1.0..1.0]

    return tanh(x);
}

double Neuron::transferFunctionDerivative(double x)
{
    // tanh derivative
    return 1.0 - x * x;
}

void Neuron::feedForward(const Layer &prevLayer)
{
    double sum = 0.0;

    // Sum the previous layer's outputs (which are our inputs)
    // Include the bias node from the previous layer.

    for (int n = 0; n < prevLayer.size(); ++n) {
        sum += prevLayer[n].getOutputVal() *
            prevLayer[n].outputWeights_[myIndex_].weight;
    }

    outputVal_ = Neuron::transferFunction(sum);
}

Neuron::Neuron(int numOutputs, int myIndex)
{
    for (int c = 0; c < numOutputs; ++c) {
        outputWeights_.push_back(Connection());
        outputWeights_.back().weight = randomWeight();
    }

    myIndex_ = myIndex;
}