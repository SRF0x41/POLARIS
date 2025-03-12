#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <sstream>

using namespace std;

// Define a variant to hold string, vector of strings, integer, vector of integers, double, and vector of doubles
using jsonObj = variant<string, vector<string>, int, vector<int>, double, vector<double>>;

class pJSON
{
private:
public:
    // Function to print the original message (excluding whitespaces)
    static void printOriginalMessage(vector<char> message)
    {
        cout << "Original message " << endl;
        for (int i = 0; i < message.size(); i++)
        {
            if (message[i] == ' ' || message[i] == '\n' || message[i] == '\r')
            {
                continue;
            }
            cout << message[i];
        }
        cout << "\n\n";
    }

    // Function to parse the JSON message
    static map<string, jsonObj> parseJSON3(vector<char> message)
    {
        if (message.front() != '{' && message.back() != '}')
        {
            cerr << "Invalid JSON" << endl;
        }

        printOriginalMessage(message);

        map<string, jsonObj> parsedMessage;
        string key;
        jsonObj value;

        bool key_read = false;
        for (int i = 1; i < message.size() - 1; i++) // Start from 1 and go till the second last character
        {
            if (message[i] == ' ' || message[i] == '\n' || message[i] == '\r')
            {
                continue;
            }

            if (message[i] == '"' && !key_read) // start of reading key
            {
                key = parseString(message, i);
                key_read = true;
            }

            if (key_read)
            {
                if (message[i] == '"') // String values
                {
                    string val = parseString(message, i);
                    parsedMessage[key] = val;
                    key_read = false;
                }
                else if (isdigit(message[i]) || message[i] == '-') // Numerical values
                {
                    string num_str = parseNumerical(message, i);
                    if (num_str.find('.') != string::npos) // If it contains a dot, it's a double
                    {
                        parsedMessage[key] = stod(num_str);
                    }
                    else
                    {
                        parsedMessage[key] = stoi(num_str);
                    }
                    key_read = false;
                }
                else if (message[i] == '[') // Start of an array
                {
                    cout << "Character start of parse " << message[i] << endl;
                    vector<jsonObj> num_arr = parseArray(message, i);
                    for (jsonObj n : num_arr)
                    {
                        if (auto intPtr = std::get_if<int>(&value))
                        {
                            cout << *intPtr << endl;
                        }
                        // Check if it holds a double
                        else if (auto doublePtr = std::get_if<double>(&value))
                        {
                            cout << *doublePtr << endl;
                        }
                    }
                    // parsedMessage[key] = num_arr;
                    key_read = false;
                }
            }
        }

        return parsedMessage;
    }

    // Helper function to parse a string (key or value)
    static string parseString(vector<char> message, int &i)
    {
        i++; // Skip the initial quote
        vector<char> data;
        while (message[i] != '"')
        {
            data.push_back(message[i]);
            i++;
        }
        i++; // Skip the closing quote
        return string(data.begin(), data.end());
    }

    // Helper function to parse numerical values (integers and doubles)
    static string parseNumerical(vector<char> message, int &i)
    {

        vector<char> num;
        while (isdigit(message[i]) || message[i] == '.' || message[i] == '-')
        {
            cout << "       parsingNumerical message at " << message[i] << endl;
            num.push_back(message[i]);
            i++;
        }
        return string(num.begin(), num.end());
    }

    // Helper function to parse arrays (ints, doubles of a single type)
    static vector<jsonObj> parseArray(vector<char> message, int &i)
    {
        vector<jsonObj> num_arr;
        while (message[i] != ']' && i < message.size())
        {
            
            cout << "   char parse " << message[i] << endl;
            if (isdigit(message[i]) || message[i] == '-') // Numerical values
            {
                string num_str = parseNumerical(message, i);
                if (num_str.find('.') != string::npos) // If it contains a dot, it's a double
                {
                    double numerical = stod(num_str);
                    num_arr.push_back(numerical);
                }
                else
                {
                    int numerical = stoi(num_str);
                    num_arr.push_back(numerical);
                }
            }
            i++;
        }
        cout << "   array parse terminator " << message[i] << endl;
        return num_arr;
    }

    // Function to print the parsed map
    static void printMap(map<string, jsonObj> parsedMessage)
    {
        for (const auto &[key, value] : parsedMessage)
        {
            cout << key << ": ";
            // Check if the variant holds a string
            if (auto strPtr = std::get_if<string>(&value))
            {
                cout << *strPtr << endl;
            }
            // Check if it holds an integer
            else if (auto intPtr = std::get_if<int>(&value))
            {
                cout << *intPtr << endl;
            }
            // Check if it holds a double
            else if (auto doublePtr = std::get_if<double>(&value))
            {
                cout << *doublePtr << endl;
            }
            else
            {
                cout << "Unknown type" << endl;
            }
        }
    }
};

int main()
{
    // Sample JSON string
    string ssJSON = R"({
        "key1": "value1",
        "key4": "value4",
        "key5": "value5",
        "key6": 42,
        "key7": 3.14159,
        "key8": "Hello, World!",
        "int_array": [1, 2, 3, 4, 5],
        "double_array": [1.1, 2.2, 3.3, 4.4, 5.5]
    })";

    // Convert string to vector<char>
    vector<char> ssVector(ssJSON.begin(), ssJSON.end());
    map<string, jsonObj> parsed_message = pJSON::parseJSON3(ssVector);

    // Print the parsed map
    cout << "Parsed JSON map:" << endl;
    pJSON::printMap(parsed_message);

    return 0;
}
