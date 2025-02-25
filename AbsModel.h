#ifndef ABSMODEL_H
#define ABSMODEL_H

#include <torch/torch.h>
#include <iostream>

class AbsModel : public torch::nn::Module {
public:
    // Pure virtual function to enforce implementation in derived classes
    virtual torch::Tensor forward(torch::Tensor x) = 0;

    // Function to train the model
    void train_model(torch::data::datasets::MNIST& dataset, int epochs, float learning_rate);

    // Destructor
    virtual ~AbsModel() = default;
};

#endif
