#include <torch/torch.h>
#include <iostream>
#include "NeuralNet.cpp" // Ensure that the AbsModel is properly included

using namespace std;

/*** Function Prototypes ***/
// Eventualy make a header file?
void usageExample();

int main()
{
    // Create an instance of NeuralNet with a 3-layer MLP (Input: 10, Hidden: 50, Output: 2)
    NeuralNet model({10, 50, 2});
    cout << "Running " << model.deviceType() << "\n";

    // Test data
    // Create a random input tensor (4 samples, each with 10 features)
    torch::Tensor inputs = torch::randn({4, 10}); // Shape: [4, 10]

    // Create random target tensor (4 samples, each with a target label)
    torch::Tensor targets = torch::randint(0, 2, {4}); // Binary labels (0 or 1), Shape: [4]

    // Print the tensors
    std::cout << "Input Tensor: \n"
              << inputs << std::endl;
    std::cout << "Target Tensor: \n"
              << targets << std::endl;

    // Test training function
    model.trainModel(0.01, 5000, inputs, targets);

    return 0;
}

void usageExample()
{
    // Set device (use CUDA if available, otherwise CPU)
    // Possibly move this to the AbsModel constructor
    torch::Device device(torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);
    std::cout << "Using device: " << (device.is_cuda() ? "CUDA" : "CPU") << std::endl;

    // Create an instance of AbsModel with a 3-layer MLP (Input: 10, Hidden: 50, Output: 2)
    // Could be multiple layers for example 4-layer MLP {10,20,30,5}
    NeuralNet model({10, 50, 2}); // This line creates the model instance

    // Move the model to the correct device (CPU or CUDA)
    model.to(device);

    // Example input tensor (batch of 5 samples, 10 features each)
    torch::Tensor input = torch::randn({5, 10}).to(device);

    // Run the model on the input
    torch::Tensor output = model.forward(input);

    std::cout << output << std::endl;
}
