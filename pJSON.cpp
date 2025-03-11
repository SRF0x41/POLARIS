#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>

using namespace std;



class pJSON
{
private:
public:
    static map<string, string> parseJSON(vector<char> message)
    {
        if (message.front() != '{' && message.back() != '}')
        {
            cout << "Invalid JSON message" << endl;
            return map<string, string>();
        }

        vector<vector<char>> mainVec;
        vector<char> data;

        for (int i = 0; i < message.size() - 1; i++) // ignore {}
        {

            if (message[i] == '"' || message[i] == '[' || message[i] == ']')
            {
                mainVec.push_back(data);
                data.clear();
            }
            else
            {
                data.push_back(message[i]);
            }
        }

        // cout << "Main vec size: " << mainVec.size() << endl;

        for (vector<char> n : mainVec)
        {
            // cout << n << endl; // Convert vector<char> to string
        }

        // Make this a one pass operation by integrating to the top loop
        map<string, string> parsedMessage;
        string key;
        string value;
        bool toggleKey = true;
        for (int i = 1; i < mainVec.size(); i++) // Ensure the condition checks until the end of the vector
        {
            if (mainVec[i].front() == ':' || mainVec[i].front() == ',')
            {
                continue;
            }
            if (toggleKey)
            {
                key = string(mainVec[i].begin(), mainVec[i].end()); // Assign key
            }
            else
            {
                value = string(mainVec[i].begin(), mainVec[i].end()); // Assign value
                parsedMessage[key] = value;                           // Store key-value pair in map
            }
            toggleKey = !toggleKey;
        }
        // cout << "Parsed message" << parsedMessage;
        return parsedMessage;
    }

    static map<string, string> parseJSON2(vector<char> message)
    {
        if(message.front() != '{' && message.back() != '}') cerr << "Invalid json" << endl;
        
        for(int i = 0; i < message.size(); i++){
            if(message[i] == ' ' || message[i] == '\n' || message[i] == '\r'){
                continue;
            }


            cout << message[i];
        }

        return map<string, string>();
    }
};

int main()
{
    // Original JSON string
    /*
    std::string jsonString = R"({
        "string": "Hello, World!",
        "number": 1234,
        "float": 12.34,
        "boolean": true,
        "null_value": null,
        "array": [1, 2, 3, 4, 5],
        "object": {
            "nested_string": "Nested",
            "nested_number": 456,
            "nested_boolean": false
        },
        "date": "2025-03-10T00:00:00Z",
        "escaped_string": "This is a \"quoted\" string."
    })";

    */
    std::string jsonString = R"({
        "string": "Hello, World!",
        "number": 1234,
        "float": 12.34,
        "boolean": true,
        "null_value": null,
        "array": [1, 2, 3, 4, 5],
        "date": "2025-03-10T00:00:00Z",
        "escaped_string": "This is a \"quoted\" string."
    })";

    // Convert string to vector<char>
    std::vector<char> jsonVector(jsonString.begin(), jsonString.end());

    pJSON::parseJSON2(jsonVector);

    return 0;
};