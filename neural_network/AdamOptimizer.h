//
// Created by Martin Galajda on 01/11/2018.
//
#define _GLIBCXX_USE_CXX11_ABI 0

#ifndef MATRIXBENCHMARKS_ADAMOPTIMIZER_H
#define MATRIXBENCHMARKS_ADAMOPTIMIZER_H

#include "BaseOptimizer.h"

class AdamOptimizer: public BaseOptimizer {
public:
    using BaseOptimizer::BaseOptimizer;
    AdamOptimizer(
            ComputationalGraph &computationalGraph,
            std::vector<std::shared_ptr<Matrix<double>>> &instances,
            std::vector<std::shared_ptr<Matrix<double>>> &labels,
            std::vector<int> &trainIndices,
            int minibatchSize,
            double learningRate
    );

    virtual void train();
protected:

    double beta1 = 0.9;
    double beta2 = 0.999;

    double epsilon = 1e-8;

    double timestep = 0;
    double epsilonCorrection = 1e-8;

    std::vector<std::shared_ptr<Matrix<double>>> gradientAverages;
    std::vector<std::shared_ptr<Matrix<double>>> squaredGradientAverages;

    std::vector<std::shared_ptr<Matrix<double>>> gradientAveragesBiases;
    std::vector<std::shared_ptr<Matrix<double>>> squaredGradientAveragesBiases;
};


#endif //MATRIXBENCHMARKS_ADAMOPTIMIZER_H