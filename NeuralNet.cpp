#include <torch/torch.h>
#include <iostream>

using namespace std;

// torch::nn::Module inheritance for moving to GPU
class NeuralNet : public torch::nn::Module
{
private:
    // Define the layers of the model
    torch::nn::Sequential layers;

    // Declare static device (shared across all objects)
    static torch::Device device;

public:
    /*** Constructors ***/
    NeuralNet()
    {
        this->to(device);
    }

    // Constructor that takes a list of layer sizes (like an MLP)
    // Create an instance of NeuralNet with a 3-layer MLP (Input: 10, Hidden: 50, Output: 2)
    // NeuralNet model({10, 50, 2});

    NeuralNet(std::vector<int64_t> layer_sizes)
    {
        // Dynamically create layers based on layer_sizes
        for (size_t i = 0; i < layer_sizes.size() - 1; ++i)
        {
            layers->push_back(torch::nn::Linear(layer_sizes[i], layer_sizes[i + 1]));
            layers->push_back(torch::nn::ReLU()); // Add ReLU activation after each layer (optional)
        }
        // Register the layers as part of the model
        register_module("layers", layers);
        this->to(device);
    }

    /* Getters */
    int getOutputSize()
    {
        // Get the last layer
        auto last_layer = layers->module_list().back();

        if (auto linear = dynamic_cast<torch::nn::Linear *>(last_layer.get()))
        {
            return linear->out_features; // Return the number of output neurons
        }
        return -1; // Return -1 if the last layer is not Linear
    }

    int getInputSize()
    {
        // Get the first layer
        auto first_layer = layers->module_list()[0];

        if (auto linear = dynamic_cast<torch::nn::Linear *>(first_layer.get()))
        {
            return linear->in_features; // Return the number of input features
        }
        return -1;
    }

    /*** Functions ***/
    // The forward pass that defines how data flows through the model
    torch::Tensor forward(torch::Tensor x)
    {
        x = x.to(device);
        return layers->forward(x); // Pass the input through all layers
    }

    // Training function
    void trainModel(float learningRate, uint64_t num_epochs, torch::Tensor inputs, torch::Tensor targets)
    {
        // Move inputs and targets to the device
        inputs = inputs.to(device);
        targets = targets.to(device);

        // Loss function (cross-entropy for classification)
        auto loss_fn = torch::nn::CrossEntropyLoss();

        // Optimizer (Stochastic Gradient Descent)
        torch::optim::SGD optimizer(this->parameters(), torch::optim::SGDOptions(learningRate));

        // Training loop
        for (uint64_t epoch = 0; epoch < num_epochs; ++epoch)
        {
            this->train();         // Set model to training mode
            optimizer.zero_grad(); // Zero gradients

            // Forward pass
            torch::Tensor output = this->forward(inputs);

            // Calculate loss
            torch::Tensor loss = loss_fn(output, targets);

            // Backward pass and optimization
            loss.backward();
            optimizer.step();

            // Print loss
            std::cout << "Epoch [" << epoch + 1 << "/" << num_epochs << "] Loss: " << loss.item<float>() << std::endl;
        }
    }

    // Get device type (CUDA or CPU)
    string deviceType()
    {
        return (device.is_cuda() ? "CUDA" : "CPU");
    }

    vector<double> normalizeData(vector<int> data)
    {
        /* formuala
        x' = 2 * ((x-min(x))/(max - min ))-1
        */

        double max_val = *max_element(data.begin(), data.end());
        double min_val = *min_element(data.begin(), data.end());

        if (max_val == min_val)
        {
            return vector<double>(data.size(), 0.0);
        }

        vector<double> norm_vec;
        for (int n : data)
        {
            norm_vec.push_back(2.0 * ((static_cast<double>(n) - min_val) / (max_val - min_val)) - 1);
        }

        return norm_vec;
    }

    /*** Examples ***/
    void trainModelExample(float learningRate)
    {
        // Loss function (cross-entropy for classification)
        auto loss_fn = torch::nn::CrossEntropyLoss();

        // Optimizer (Stochastic Gradient Descent)
        torch::optim::SGD optimizer(this->parameters(), torch::optim::SGDOptions(learningRate));

        // Dummy data (for example purposes: batch size = 16, features = 10)
        torch::Tensor inputs = torch::randn({16, 10}).to(device);
        torch::Tensor targets = torch::randint(0, 2, {16}).to(device); // Random binary targets for classification

        // Training loop
        int64_t num_epochs = 5;
        for (int epoch = 0; epoch < num_epochs; ++epoch)
        {
            this->train();         // Set model to training mode
            optimizer.zero_grad(); // Zero gradients

            // Forward pass
            torch::Tensor output = this->forward(inputs);

            // Calculate loss
            torch::Tensor loss = loss_fn(output, targets);

            // Backward pass and optimization
            loss.backward();
            optimizer.step();

            // Print loss
            std::cout << "Epoch [" << epoch + 1 << "/" << num_epochs << "] Loss: " << loss.item<float>() << std::endl;
        }
    }
};

// Initialize the device before any instance of the class is present
torch::Device NeuralNet::device(torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);
