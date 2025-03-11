#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>

using namespace std;
using jsonObj = variant<string>;

class pJSON
{
private:
public:
    static map<string, jsonObj> parseJSON2(vector<char> message)
    {
        if (message.front() != '{' && message.back() != '}')
            cerr << "Invalid json" << endl;

        cout << "Original message " << endl;
        for (int i = 1; i < message.size() - 1; i++)
        {
            if (message[i] == ' ' || message[i] == '\n' || message[i] == '\r')
            {
                continue;
            }
            cout << message[i];
        }
        cout << "\n\n";

        // keep reading untill the stack terminates
        map<string, jsonObj> parsed_message;
        vector<char> delim_stack; // valid terminators " " : ,

        vector<vector<char>> main_vec;
        vector<char> data;

        for (int i = 1; i < message.size() - 1; i++)
        {
            if (message[i] == ' ' || message[i] == '\n' || message[i] == '\r')
            {
                continue;
            }

            // read key
            if (message[i] == '"')
            {
                i++;
                while (message[i] != '"')
                {
                    data.push_back(message[i]);
                    i++;
                }
                i++;
                parsed_message[string(data.begin(), data.end())] = "placeholder";

                cout << "key " << string(data.begin(), data.end()) << endl;
                main_vec.push_back(data);
                data.clear();
            }
            cout << "inter json delim " << message[i] << endl;

            // read value
            if (message[i] == ':')
            {
                delim_stack.push_back(':');
                i++;
                while (!delim_stack.empty())
                {
                    if (delim_stack.back() == ':' && message[i] == ',') // end of read value
                    {
                        delim_stack.pop_back();
                    }
                    if (delim_stack.back() == '[' && message[i] == ']')
                    {
                        delim_stack.pop_back();
                    }
                }
            }
        }

        // printMap(parsed_message);
        return parsed_message;
    }

    static map<string, jsonObj> parseJSON3(vector<char> message)
    {
        if (message.front() != '{' && message.back() != '}')
            cerr << "Invalid json" << endl;

        cout << "Original message " << endl;
        for (int i = 1; i < message.size() - 1; i++)
        {
            if (message[i] == ' ' || message[i] == '\n' || message[i] == '\r')
            {
                continue;
            }
            cout << message[i];
        }
        cout << "\n\n";

        for (int i = 1; i < message.size() - 1; i++)
        {
            if (message[i] == ' ' || message[i] == '\n' || message[i] == '\r')
            {
                continue;
            }
        }


    }

    static void printMap(map<string, jsonObj> parsedMessage)
    {
        // Iterate over the map
        for (const auto &[key, value] : parsedMessage)
        {
            cout << key << ": ";

            // Check if the variant holds a string
            if (auto strPtr = std::get_if<string>(&value))
            {
                // If it holds a string, print the string value
                cout << *strPtr << endl;
            }
            // You can add more types here if you plan to extend jsonObj
            else
            {
                cout << "Unknown type" << endl;
            }
        }
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

    // std::vector<char> jsonVector(jsonString.begin(), jsonString.end());
    // pJSON::parseJSON2(jsonVector);

    std::string ssJSON = R"({
    "key1": "value1",
    "key2": "value2",
    "key3": "value3",
    "key4": "value4",
    "key5": "value5"
    })";

    // Convert string to vector<char>

    vector<char> ssVector(ssJSON.begin(), ssJSON.end());
    map<string, jsonObj> parsed_message = pJSON::parseJSON2(ssVector);
    cout << "print map" << endl;
    pJSON::printMap(parsed_message);

    return 0;
};