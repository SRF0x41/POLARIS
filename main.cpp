#include <torch/torch.h>
#include <iostream>
#include "model.h"

int main() {
    // Set device (use CUDA if available, otherwise CPU)
    torch::Device device(torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);
    std::cout << "Using device: " << (device.is_cuda() ? "CUDA" : "CPU") << std::endl;

    // Create model and move it to the selected device
    Net model;
    model.to(device);

    // Define loss function and optimizer
    torch::nn::CrossEntropyLoss loss_fn;
    torch::optim::SGD optimizer(model.parameters(), torch::optim::SGDOptions(0.01)); // Learning rate = 0.01

    // Dummy data (batch_size = 1, input_size = 784)
    torch::Tensor input = torch::randn({1, 784}).to(device);
    torch::Tensor target = torch::tensor({3}, torch::kLong).to(device); // Class label 3

    // Training step
    model.train();
    optimizer.zero_grad();  // Reset gradients
    torch::Tensor output = model.forward(input);
    torch::Tensor loss = loss_fn(output, target);
    loss.backward();  // Backpropagation
    optimizer.step();  // Update weights

    std::cout << "Loss: " << loss.item<float>() << std::endl;

    return 0;
}
