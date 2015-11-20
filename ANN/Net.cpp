#include "Net.h"
#include <iostream>
#include <cassert>

using namespace std;
using namespace ANN;
double Net::recentAverageSmoothingFactor_ = 100.0; // Number of training samples to average over

void Net::getResults(vector<double> &resultVals) const
{
    resultVals.clear();

    for (int n = 0; n < layers_.back().size() - 1; ++n) {
        resultVals.push_back(layers_.back()[n].getOutputVal());
    }
}

void Net::backProp(const vector<double> &targetVals)
{
    // Calculate overall net error (RMS of output neuron errors)

    Layer &outputLayer = layers_.back();
    error_ = 0.0;

    for (int n = 0; n < outputLayer.size() - 1; ++n) {
        double delta = targetVals[n] - outputLayer[n].getOutputVal();
        error_ += delta * delta;
    }
    error_ /= outputLayer.size() - 1; // get average error squared
    error_ = sqrt(error_); // RMS

                             // Implement a recent average measurement

    recentAverageError_ =
        (recentAverageError_ * recentAverageSmoothingFactor_ + error_)
        / (recentAverageSmoothingFactor_ + 1.0);

    // Calculate output layer gradients

    for (int n = 0; n < outputLayer.size() - 1; ++n) {
        outputLayer[n].calcOutputGradients(targetVals[n]);
    }

    // Calculate hidden layer gradients

    for (size_t layerNum = layers_.size() - 2; layerNum > 0; --layerNum) {
        Layer &hiddenLayer = layers_[layerNum];
        Layer &nextLayer = layers_[layerNum + 1];

        for (int n = 0; n < hiddenLayer.size(); ++n) {
            hiddenLayer[n].calcHiddenGradients(nextLayer);
        }
    }

    // For all layers from outputs to first hidden layer,
    // update connection weights

    for (size_t layerNum = layers_.size() - 1; layerNum > 0; --layerNum) {
        Layer &layer = layers_[layerNum];
        Layer &prevLayer = layers_[layerNum - 1];

        for (int n = 0; n < layer.size() - 1; ++n) {
            layer[n].updateInputWeights(prevLayer);
        }
    }
}

void Net::feedForward(const vector<double> &inputVals)
{
    assert(inputVals.size() == layers_[0].size() - 1);

    // Assign (latch) the input values into the input neurons
    for (int i = 0; i < inputVals.size(); ++i) {
        layers_[0][i].setOutputVal(inputVals[i]);
    }

    // forward propagate
    for (int layerNum = 1; layerNum < layers_.size(); ++layerNum) {
        Layer &prevLayer = layers_[layerNum - 1];
        for (int n = 0; n < layers_[layerNum].size() - 1; ++n) {
            layers_[layerNum][n].feedForward(prevLayer);
        }
    }
}

Net::Net(const vector<int> &topology)
{
    size_t numLayers = topology.size();
    for (int layerNum = 0; layerNum < numLayers; ++layerNum) {
        layers_.push_back(Layer());
        int numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

        // We have a new layer, now fill it with neurons, and
        // add a bias neuron in each layer.
        for (int neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
            layers_.back().push_back(Neuron(numOutputs, neuronNum));
            cout << "Made a Neuron!" << endl;
        }

        // Force the bias node's output to 1.0 (it was the last neuron pushed in this layer):
        layers_.back().back().setOutputVal(1.0);
    }
}
