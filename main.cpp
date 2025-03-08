#include <torch/torch.h>
#include <iostream>
#include "NeuralNet.cpp" // Ensure that the AbsModel is properly included
#include "SocketComm.cpp"
#include <string>

using namespace std;

/*** Function Prototypes ***/
// Eventualy make a header file?
void usageExample();

int main()
{
    SocketComm sock_comm;

    string input;

    // Continually ask for input until "exit" is entered
    while (true)
    {
        cout << "Enter something (type 'exit' to quit): ";
        getline(cin, input); // Get the entire line of input

        // Check if the user wants to exit
        if (input == "exit")
        {
            std::cout << "Exiting program." << std::endl;
            break; // Break the loop if "exit" is entered
        }

        // Serialize string to char*
        size_t data_len = input.size() + 1;
        char* data_arr = new char[data_len];
        memcpy(data_arr, input.c_str(), data_len);

        sock_comm.sendMessage(data_arr);

        cout << "You entered: " << input << std::endl;
    }

    sock_comm.closeSocket();

    /*
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
    */

    return 0;
}
