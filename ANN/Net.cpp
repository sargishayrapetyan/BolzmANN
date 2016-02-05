#include "Net.h"
#include <iostream>
#include <cassert>

using namespace ANN;

double Net::recentAverageSmoothingFactor_ = 100.0; // Number of training samples to average over

vector<double> Net::getResults() const
{
    vector<double> resultVals;

    const auto& backLayer = layers_.back();

    auto       it    = backLayer.begin();
    const auto itEnd = backLayer.end() - 1;
    for (; it != itEnd; ++it) 
    {
        resultVals.emplace_back(it->getOutputVal());
    }
    return resultVals;
}
void Net::backProp(const vector<double>& targetVals)
{
    // Calculate overall net error (RMS of output neuron errors)

    auto& outputLayer = layers_.back();
    error_ = 0.0;

    for (int n = 0; n < outputLayer.size() - 1; ++n) 
    {
        double delta = targetVals[n] - outputLayer[n].getOutputVal();
        error_ += delta * delta;
    }
    error_ /= outputLayer.size() - 1; // get average error squared
    error_ = sqrt(error_);            // RMS

    // Implement a recent average measurement
    recentAverageError_ = (recentAverageError_ * recentAverageSmoothingFactor_ + error_)
                        / (                      recentAverageSmoothingFactor_ + 1.0);

    // Calculate output layer gradients

    for (int n = 0; n < outputLayer.size() - 1; ++n) 
    {
        outputLayer[n].calcOutputGradients(targetVals[n]);
    }

    // Calculate hidden layer gradients

    for (size_t layerNum = layers_.size() - 2; layerNum > 0; --layerNum) 
    {
        Layer& hiddenLayer = layers_[layerNum];
        Layer& nextLayer   = layers_[layerNum + 1];

        for (auto& neuron : hiddenLayer) 
        {
            neuron.calcHiddenGradients(nextLayer);
        }
    }

    // For all layers from outputs to first hidden layer,
    // update connection weights

    for (size_t layerNum = layers_.size() - 1; layerNum > 0; --layerNum) 
    {
        Layer& layer     = layers_[layerNum];
        Layer& prevLayer = layers_[layerNum - 1];

        for (int n = 0; n < layer.size() - 1; ++n) 
        {
            layer[n].updateInputWeights(prevLayer);
        }
    }
}

void Net::feedForward(const vector<double>& inputVals)
{
    assert(inputVals.size() == layers_[0].size() - 1);

    // Assign (latch) the input values into the input neurons
    for (int i = 0; i < inputVals.size(); ++i) 
    {
        layers_[0][i].setOutputVal(inputVals[i]);
    }

    // Forward propagate
    for (int layerNum = 1; layerNum < layers_.size(); ++layerNum) 
    {
        Layer& prevLayer = layers_[layerNum - 1];
        for (int n = 0; n < layers_[layerNum].size() - 1; ++n) 
        {
            layers_[layerNum][n].feedForward(prevLayer);
        }
    }
}

Net::Net(const vector<int>& topology) : error_(0.0), recentAverageError_(0.0)
{
    size_t numLayers = topology.size();

    for (int layerNum = 0; layerNum < numLayers; ++layerNum) 
    {
        layers_.emplace_back(Layer());
        int numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

        // We have a new layer, now fill it with neurons,
        // and add a bias neuron in each layer.
        const auto L = topology[layerNum];
        for (int neuronNum = 0; neuronNum <= L; ++neuronNum)
        {
            layers_.back().emplace_back(Neuron(numOutputs, neuronNum));
            cout << "Neuron made." << endl;
        }

        // Force the bias node's output to 1.0 (it was the last neuron pushed in this layer):
        layers_.back().back().setOutputVal(1.0);
    }
}
