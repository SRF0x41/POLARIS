#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <sstream>

using namespace std;

using jsonObj = variant<string, vector<string>, int, vector<int>, double, vector<double>>;

class pJSON
{
private:
    map<string, jsonObj> json_obj_map;
    vector<string> keys;
    vector<char> original_message;

    string parseString(vector<char> message, int &i)
    {
        i++;
        vector<char> data;
        while (message[i] != '"')
        {
            data.push_back(message[i++]);
        }
        i++;
        return string(data.begin(), data.end());
    }

    string parseNumerical(vector<char> message, int &i)
    {
        vector<char> num;
        while (isdigit(message[i]) || message[i] == '.' || message[i] == '-')
        {
            num.push_back(message[i++]);
        }
        return string(num.begin(), num.end());
    }

    jsonObj parseArray(vector<char> message, int &i)
    {
        vector<int> intArr;
        vector<double> doubleArr;
        bool isDouble = false;

        while (message[i] != ']')
        {
            i++;
            if (isdigit(message[i]) || message[i] == '-')
            {
                string num_str = parseNumerical(message, i);
                if (num_str.find('.') != string::npos)
                {
                    isDouble = true;
                    doubleArr.push_back(stod(num_str));
                }
                else
                {
                    intArr.push_back(stoi(num_str));
                }
            }
        }
        i++;
        return isDouble ? jsonObj(doubleArr) : jsonObj(intArr);
    }

public:
    pJSON()
    {
    }
    pJSON(vector<char> message)
    {
        original_message = message;
        parseJSON(message);
    }
    /* Getters */
    vector<string> getKeys()
    {
        return keys;
    }

    jsonObj getValue(string key)
    {
        return json_obj_map[key];
    }

    void printOriginalMessage(vector<char> message)
    {
        cout << "Original message " << endl;
        for (char c : message)
        {
            if (c != ' ' && c != '\n' && c != '\r')
            {
                cout << c;
            }
        }
        cout << "\n\n";
    }

    void printOriginalMessage()
    {
        cout << "Original message " << endl;
        for (char c : original_message)
        {
            if (c != ' ' && c != '\n' && c != '\r')
            {
                cout << c;
            }
        }
        cout << "\n\n";
    }

    void parseJSON(vector<char> message)
    {
        if (!original_message.empty())
        {
            original_message = message;
        }

        if (message.front() != '{' || message.back() != '}')
        {
            cerr << "Invalid JSON" << endl;
        }
        string key;
        bool key_read = false;

        for (int i = 1; i < message.size() - 1; i++)
        {
            // Skip over spaces and escape codes
            if (message[i] == ' ' || message[i] == '\n' || message[i] == '\r')
            {
                continue;
            }

            // Start of reading a key
            if (message[i] == '"' && !key_read)
            {
                key = parseString(message, i);
                key_read = true;
                keys.push_back(key);
            }

            // Once the key is read, read the associated value
            if (key_read)
            {
                if (message[i] == '"') // String value
                {
                    json_obj_map[key] = parseString(message, i);
                    key_read = false;
                }
                else if (isdigit(message[i]) || message[i] == '-') // numerical value
                {
                    string num_str = parseNumerical(message, i);
                    json_obj_map[key] = (num_str.find('.') != string::npos) ? stod(num_str) : stoi(num_str);
                    key_read = false;
                }
                else if (message[i] == '[') // array value
                {
                    jsonObj arrayValue = parseArray(message, i);
                    json_obj_map[key] = arrayValue;
                    key_read = false;
                }
            }
        }
    }

    void printMessage()
    {
        for (const auto &[key, value] : this->json_obj_map)
        {
            cout << key << ": ";
            if (auto strPtr = get_if<string>(&value))
            {
                cout << *strPtr << endl;
            }
            else if (auto intPtr = get_if<int>(&value))
            {
                cout << *intPtr << endl;
            }
            else if (auto doublePtr = get_if<double>(&value))
            {
                cout << *doublePtr << endl;
            }
            else if (auto intVecPtr = get_if<vector<int>>(&value))
            {
                for (int num : *intVecPtr)
                    cout << num << " ";
                cout << endl;
            }
            else if (auto doubleVecPtr = get_if<vector<double>>(&value))
            {
                for (double num : *doubleVecPtr)
                    cout << num << " ";
                cout << endl;
            }
            else
            {
                cout << "Unknown type" << endl;
            }
        }
    }
};
/*
int main()
{
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

    vector<char> ssVector(ssJSON.begin(), ssJSON.end());

    pJSON parser;
    parser.parseJSON(ssVector);
    parser.printOriginalMessage();
    parser.printMap();

    string newJSON = R"({
        "username": "john_doe",
        "status": "active",
        "email": "johndoe@example.com",
        "age": 30,
        "score": 99.75,
        "message": "Welcome to the system!",
        "int_array": [10, 20, 30, 40, 50],
        "double_array": [2.5, 3.6, 7.8, 9.9, 12.1]
    })";

    vector<char> newVector(newJSON.begin(), newJSON.end());

    parser.parseJSON(newVector);
    parser.printOriginalMessage();
    parser.printMap();

    return 0;
}
*/