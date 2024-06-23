#include <string>
#include <regex>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

bool isValidRegex(const std::string& pattern) {
    try {
        std::regex re(pattern);
    }
    catch (const std::regex_error& e) {
        return false;
    }
    return true;
}


class Extend {

public:

    Extend() {}

    Extend(string name, string regex) {
        this->name = name;
        bool flag = isValidRegex(regex);
        if (regex == "*") {
            this->regex = "^.*$";
        }
        else if (!flag) {
            this->regex = "^.*$";
        }
        else {
            this->regex = regex;
        }
    }

public:

    string name;

    string regex;

    string val;
};