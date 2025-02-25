#include "model.h"

// Constructor: Initialize the layers
Net::Net() {
    // Define layers with input/output sizes
    fc1 = register_module("fc1", torch::nn::Linear(784, 128)); // 784 input features → 128 hidden neurons
    fc2 = register_module("fc2", torch::nn::Linear(128, 64));  // 128 → 64
    fc3 = register_module("fc3", torch::nn::Linear(64, 10));   // 64 → 10 (output for classification)
}

// Forward function: Define the forward pass
torch::Tensor Net::forward(torch::Tensor x) {
    x = torch::relu(fc1->forward(x));  // Activation after first layer
    x = torch::relu(fc2->forward(x));  // Activation after second layer
    x = fc3->forward(x);               // No activation in final layer (use Softmax or CrossEntropyLoss later)
    return x;
}

// Explicit template instantiation (useful for preventing linker errors)
template class torch::nn::ModuleHolder<Net>;
