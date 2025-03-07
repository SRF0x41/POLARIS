#include <torch/torch.h>
#include <iostream>

using namespace std;

// torch::nn::Module inheretance for moving to GPU
class AbsModel : public torch::nn::Module
{
private:
    // Define the layers of the model
    torch::nn::Sequential layers;

    // Declare static device (shared across all objects)
    /* Set the device globaly, therefore this is a static object */
    static torch::Device device;

public:
    /*** Constructors ***/
    AbsModel()
    {
        this->to(device);
    }
    // Constructor that takes a list of layer sizes (like an MLP)
    // Create an instance of AbsModel with a 3-layer MLP (Input: 10, Hidden: 50, Output: 2)
    // Could be multiple layers for example 4-layer MLP {10,20,30,5}s
    AbsModel(std::vector<int64_t> layer_sizes)
    {
        // Dynamically create layers based on layer_sizes
        for (size_t i = 0; i < layer_sizes.size() - 1; ++i)
        {
            // Each torch::nn::Linear(in_features, out_features)
            // layer connects layer_sizes[i] neurons to layer_sizes[i+1] neurons.
            layers->push_back(torch::nn::Linear(layer_sizes[i], layer_sizes[i + 1]));
            layers->push_back(torch::nn::ReLU()); // Add ReLU activation after each layer (optional)
        }
        // Register the layers as part of the model
        register_module("layers", layers);
        this->to(device);
    }

    /*** Functions ***/

    // The forward pass that defines how data flows through the model
    torch::Tensor forward(torch::Tensor x)
    {
        return layers->forward(x); // Pass the input through all layers
    }


    /** Getters **/
    string deviceType(){
        return (device.is_cuda() ? "CUDA" : "CPU");
    }
};

// Initialises the device before any instance of the class is present
// Define the static device variable
torch::Device AbsModel::device(torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);
