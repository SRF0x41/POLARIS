#include <torch/torch.h>
#include <iostream>

class AbsModel : public torch::nn::Module {
private:
    // Define the layers of the model
    torch::nn::Sequential layers;

public:
    // Constructor that takes a list of layer sizes (like an MLP)
    AbsModel(std::vector<int64_t> layer_sizes) {
        // Dynamically create layers based on layer_sizes
        for (size_t i = 0; i < layer_sizes.size() - 1; ++i) {
            layers->push_back(torch::nn::Linear(layer_sizes[i], layer_sizes[i + 1]));
            layers->push_back(torch::nn::ReLU()); // Add ReLU activation after each layer (optional)
        }
        // Register the layers as part of the model
        register_module("layers", layers);
    }

    // The forward pass that defines how data flows through the model
    torch::Tensor forward(torch::Tensor x) {
        return layers->forward(x);  // Pass the input through all layers
    }
};
