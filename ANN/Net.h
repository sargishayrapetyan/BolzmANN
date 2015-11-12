#ifndef  NET_H
#define  NET_H

#include "Neuron.h"
using namespace std;

class Net
{
public:
    Net(const vector<int> &topology);
    void feedForward(const vector<double> &inputVals);
    void backProp(const vector<double> &targetVals);
    void getResults(vector<double> &resultVals) const;
    double getRecentAverageError() const { return recentAverageError_; }

private:
    vector<Layer> layers_; // layers_[layerNum][neuronNum]
    double error_;
    double recentAverageError_;
    static double recentAverageSmoothingFactor_;
};

#endif // NET_H
