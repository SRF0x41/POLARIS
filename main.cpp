#include <torch/torch.h>
#include <iostream>
#include "AbsModel.cpp"  // Ensure that the AbsModel is properly included

int main() {
    // Set device (use CUDA if available, otherwise CPU)
    torch::Device device(torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);
    std::cout << "Using device: " << (device.is_cuda() ? "CUDA" : "CPU") << std::endl;

    // Create an instance of AbsModel with a 3-layer MLP (Input: 10, Hidden: 50, Output: 2)
    AbsModel model({10, 50, 2});  // This line creates the model instance

    // Move the model to the correct device (CPU or CUDA)
    model.to(device);

    // Example input tensor (batch of 5 samples, 10 features each)
    torch::Tensor input = torch::randn({5, 10}).to(device);

    // Run the model on the input
    torch::Tensor output = model.forward(input);

    std::cout << output << std::endl;

    return 0;
}
