#pragma once  // Prevent multiple inclusions of this file

#include <torch/torch.h>

// Define a simple neural network class
class Net : public torch::nn::Module {
public:
    // Layers
    torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr};

    // Constructor
    Net();

    // Forward function
    torch::Tensor forward(torch::Tensor x);
};
