# POLARIS: Processing, Learning, and Reasoning in Small-data AI (Under Construction)
*Developing a CUDA-accelerated AI framework designed for efficient AI development with smaller datasets and multimodal capabilities. POLARIS simplifies AI model creation and optimization, enabling seamless integration of multiple data types.*

This repository contains a neural network model implemented using **LibTorch (C++ API for PyTorch)**. The neural network is designed to run on both **CPU** and **GPU** (CUDA) depending on availability.

## Project Vision

The primary goal of POLARIS is to enable AI models that are highly flexible in learning new data in real-time. Unlike traditional models, which require full retraining when new data is introduced, POLARIS allows the model to incrementally update with new data. This capability is inspired by the neural structure of the human brain, which selectively trains smaller, discrete neural networks instead of retraining the entire brain. By mimicking this process, POLARIS aims to improve the efficiency and adaptability of AI models, particularly in scenarios with smaller or constantly evolving datasets.

The inspiration comes from how the brain processes information. In the brain, it’s not always necessary to modify every neural pathway when new information is learned. Instead, only relevant parts of the neural network are selectively updated, allowing for efficient learning. Similarly, POLARIS seeks to implement a more efficient AI training methodology by focusing on incremental updates rather than large-scale retraining, which can be resource-intensive and time-consuming.

The project aims to build AI systems that can quickly adapt and optimize themselves when exposed to new data, improving the overall performance in real-time applications, especially for domains with limited data availability.

## Table of Contents

- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Progress](#progress)

## Requirements

To run this project, you will need the following:

- C++17 or later
- [LibTorch](https://pytorch.org/cppdocs/) (The C++ distribution of PyTorch)
- CMake (for building the project)
- A compatible GPU with CUDA (optional, but recommended for faster training)

### Libraries/Dependencies

- PyTorch C++ API (LibTorch)
- CMake for building the project

## Installation

1. **Download LibTorch:**
   - Visit the [LibTorch download page](https://pytorch.org/get-started/locally/) and download the version matching your system and CUDA version (if using a GPU).
   
2. **Set up the project:**
   - Clone this repository or download the project files.
   - Install CMake if not already installed.
   - Create a `build` directory:
     ```bash
     mkdir build
     cd build
     ```
   - Run CMake to configure the project:
     ```bash
     cmake ..
     ```
   - Build the project:
     ```bash
     cmake --build .
     ```

## Usage

Once the project is set up and compiled, you can use the neural network model to define, train, and evaluate a neural network.

### Example of Running the Model

In the provided example, we create a model with 3 layers: an input layer, a hidden layer, and an output layer. The model is trained on random data for 5000 epochs.

1. **Define the Model:**
    ```cpp
    // Create an instance of NeuralNet with a 3-layer MLP (Input: 10, Hidden: 50, Output: 2)
    NeuralNet model({10, 50, 2});

    // Check what type of device its running on (CUDA or CPU)
    cout << "Running " << model.deviceType() << "\n";
    ```

2. **Create Tensors with Inputs and Targets:**
    ```cpp
    // Create a random input tensor (4 samples, each with 10 features)
    torch::Tensor inputs = torch::randn({4, 10}); // Shape: [4, 10]

    // Create random target tensor (4 samples, each with a target label)
    torch::Tensor targets = torch::randint(0, 2, {4}); // Binary labels (0 or 1), Shape: [4]

    // Print the tensors
    std::cout << "Input Tensor: \n"  << inputs << std::endl;
    std::cout << "Target Tensor: \n" << targets << std::endl;
    ```

3. **Train the Model:**
    ```cpp
    // Learning rate: 0.01, 5000 epochs, inputs and outputs
    model.trainModel(0.01, 5000, inputs, targets);
    ```

## Progress

### Current Status

- **Model Architecture**: The very basic PyTorch inhereted class NeuralNet has been implemented. This removes a lot of manual tooling for ease of use, planning on creating more modularity with ease of use in mind.
- **CUDA Integration**: GPU acceleration is supported.
- **Training**: Initial tests with random data have been successful.
- **Multimodal Capabilities**: Work is ongoing to enable handling multiple types of data simultaneously (e.g., images, text, and tabular data). Will develop the classes and tooling required to make this seamless.
- **Documentation**: The documentation is being updated to include detailed instructions on model usage and customization.

### Planned Features

- Further optimizations for small datasets.
- Enhanced multimodal data integration.

