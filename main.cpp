#include <torch/torch.h>
#include <iostream>
#include "NeuralNet.cpp" // Ensure that the AbsModel is properly included
#include "SocketComm.cpp"
#include <string>
#include <vector>
#include "pJSON.cpp"
#include <typeinfo>
#include "ProtoLimbic.cpp"

using namespace std;
using namespace torch;
/*** Function Prototypes ***/
// Eventualy make a header file?




int main(){
    NeuralNet model({10, 50, 9});
    cout << "Running " << model.deviceType() << "\n";



    ProtoLimbic p_lim(model);
    Tensor internal_target = p_lim.internalTarget();

    cout << internal_target << endl;


    return 0;
}


/*

int main()
{
    // Socket and loop tooling
    SocketComm sock_comm;
    if (sock_comm.createConnection())
    {
        return 0;
    }
    bool running = true;

    // NN tooling
    // Create an instance of NeuralNet with a 3-layer MLP (Input: 10, Hidden: 50, Output: 2)
    NeuralNet model({10, 50, 9});
    cout << "Running " << model.deviceType() << "\n";

    while (running)
    {
        vector<char> recieved_data = sock_comm.recieveData();
        if (recieved_data.empty())
        {
            cerr << "Connection closed or empty data recieved, exiting loop. \n";
            break;
        }
        pJSON json_parser(recieved_data);
        string client_command = json_parser.getString("command");
        if (client_command == "close_client")
        {
            cout << "Server exit command recieved, closing connection.\n";
            break;
        }

        // Server data parsing
        json_parser.printMessage();
        vector<int> extracted_data = json_parser.getIntVector("data");
        int game_state = json_parser.getInt("win_state");

        // Data normalization
        vector<double> norm_data = model.normalizeData(extracted_data);
        cout << "Norm data " << norm_data << endl;

        // Covert norm data to tensor
        torch::Tensor input_tensor = torch::tensor(norm_data, torch::dtype(torch::kFloat32));
        torch::Tensor model_out = model.forward(input_tensor);

        cout << "model forwards \n";
        cout << model_out << endl;

        string test_send = R"({message:"hello from POLARIS"})";
        sock_comm.sendMessage(test_send);
    }
    cout << "Closing socket connection...\n";
    sock_comm.closeSocket(); // Ensure safe disconnection

    cout << "Socket closed. Exiting program.\n";
    return 0;
}

*/

// Continually ask for input until "exit" is entered

/*
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

    sock_comm.sendMessage(input);

    cout << "You entered: " << input << std::endl;

    vector<char> output = sock_comm.recieveData();

    //cout << output << "\n";
    pJSON parser(output);

    parser.printMessage();

}

sock_comm.closeSocket();
*/

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