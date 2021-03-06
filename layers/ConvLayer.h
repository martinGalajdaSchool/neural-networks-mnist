//
// Created by Martin Galajda on 27/11/2018.
//

#ifndef MATRIXBENCHMARKS_CONVLAYER_H
#define MATRIXBENCHMARKS_CONVLAYER_H

#include "BaseLayer.h"

namespace ConvLayerUtils {
  struct PerformConvLayerBackpropPayload {
    int thread_id;
    ActivationFunction *activationFunctionPtr;
    Matrix<double> *outDerivativesPtr;
    Matrix<double> *neuronDerivativesPtr;
    Matrix<double> *weightDerivativesPtr;
    Matrix<double> *activateInputsPtr;
    Matrix<double> *inputsPtr;
    Matrix<double> *weightsPtr;
    int *stridePtr;
  };

  void PerformConvLayerBackPropagation(PerformConvLayerBackpropPayload *payload);
}


class ConvLayer: public BaseLayer {

public:
    ConvLayer(
            int kernelWidth,
            int kernelHeight,
            int batchSize,
            int inputDepth,
            int numberOfFilters,
            BaseInitializer *initializer,
            ActivationFunction activationFunction,
            int stride,
            std::string name = "ConvLayer"
    );

    ConvLayer(
            int kernelWidth,
            int kernelHeight,
            int batchSize,
            int inputDepth,
            int numberOfFilters,
            ActivationFunction activationFunction,
            int stride,
            std::string name = "ConvLayer"
    );

    void initialize(std::shared_ptr<Matrix<double>> X);

    virtual std::shared_ptr<Matrix<double>> forwardPropagate(std::shared_ptr<Matrix<double>> X);
    virtual std::shared_ptr<Matrix<double>> activate(std::shared_ptr<Matrix<double>> &X);
    virtual std::shared_ptr<Matrix<double>> backPropagate(std::shared_ptr<Matrix<double>> forwardDerivatives, int numOfThreads);

    virtual int getLayerOutputDepth() { return this->numberOfFilters; }

    virtual bool hasBiases() { return false; }
    virtual bool hasWeights() { return true; }

protected:
    int stride;
    int kernelWidth;
    int kernelHeight;
    int inputDepth;
    int numberOfFilters;
    int inputSizeWidth;
    int inputSizeHeight;

    bool isInitialized = false;
};


#endif //MATRIXBENCHMARKS_CONVLAYER_H
