#include <iostream>
#include <cstring>      // For memset, strlen
#include <sys/socket.h> // For socket functions
#include <arpa/inet.h>  // For inet_addr, htons
#include <unistd.h>     // For close()
#include <vector>


class SocketComm
{
private:
    int client_socket;

public:
    SocketComm()
    {
    }

    int createConnection()
    {
        // Create a TCP socket
        client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket == -1)
        {
            std::cerr << "Error creating socket!\n";
            return -1;
        }

        // Define server details
        sockaddr_in server_addr{};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(12345);                  // Port must match the server
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost

        // Connect to the server
        if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        {
            std::cerr << "Connection failed!\n";
            close(client_socket);
            return -1;
        }

        std::cout << "Connected to the server!\n";

        return 0;
    }

    void sendMessage(char *message)
    {
        send(client_socket, message, strlen(message), 0);
    }

    void sendMessage(string message)
    {
        // serialize string into char*
        size_t data_len = message.size() + 1; // Include null terminator
        ssize_t bytes_sent = send(client_socket, message.c_str(), data_len, 0);

        if (bytes_sent == -1)
        {
            cerr << "Error sending message!" << endl;
        }
    }

    void receiveDataPrint()
    {
        // Receive response from server
        char buffer[1024] = {0};
        recv(client_socket, buffer, sizeof(buffer), 0);
        std::cout << "Server response: " << buffer << std::endl;
    }

    vector<char> recieveData()
    {
        // I dont want to allocate memory at the end of this function so just return as a vec
        vector<char> buffer(1024);
        int bytes_recieved = recv(client_socket, buffer.data(), buffer.size(), 0);
        buffer.resize(bytes_recieved);
        return buffer;
    }

    void closeSocket()
    {
        close(client_socket);
    }
};
