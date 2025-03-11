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

    static map<string, jsonObj> parseJSON3(vector<char> message)
    {
        if (message.front() != '{' && message.back() != '}')
            cerr << "Invalid json" << endl;

        printOriginalMessage(message);

        map<string, jsonObj> parsedMessage;
        string key;
        jsonObj value;

        bool key_read = false;
        for (int i = 1; i < message.size() - 1; i++)
        {
            if (message[i] == ' ' || message[i] == '\n' || message[i] == '\r')
            {
                continue;
            }

            if (message[i] == '"' && key_read == false) // start of read key
            {
                key = parseString(message, i);
                key_read = true;
            }

            if (key_read)
            {
                if (message[i] == '"') // start of read key
                {
                    string val = parseString(message, i);
                    key_read = false;

                    parsedMessage[key] = val;
                }
            }
        }

        return parsedMessage;
    }

    /* Key parser */
    static string parseString(vector<char> message, int &i)
    {

        i++;
        vector<char> data;
        while (message[i] != '"')
        {
            data.push_back(message[i]);
            i++;
        }
        i++;

        return string(data.begin(), data.end());
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
    map<string, jsonObj> parsed_message = pJSON::parseJSON3(ssVector);
    cout << "print map" << endl;
    pJSON::printMap(parsed_message);

    return 0;
};