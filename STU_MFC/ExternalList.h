#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include "Extend.h"

using namespace std;

class ExternalList {

    map<string, Extend> data;

public:

    void loads() {
        data.clear();
        ifstream temp("external_db.txt");
        if (!temp.good()) {
            temp.close();
            ofstream outfile("external_db.txt");
            outfile << "key    新字段  ^.*$\n";
            outfile.close();
        }
        ifstream file("external_db.txt");
        if (!file.is_open()) {
            printf("文件在另一进程中已打开\n");
            exit(1);
        }
        string line;
        while (getline(file, line)) {
            if (file.fail()) {
                printf("读取文件时出错\n");
                break;
            }
            istringstream iss(line);
            vector<string> fields;
            string field;
            while (iss >> field) {
                fields.push_back(field);
            }
            try {
                Extend save;
                if (fields.size() != 3) {
                    throw "exp";
                }

                put(fields[0], Extend(fields[1], fields[2]));

            }
            catch (...) {

            }
        }
        file.close();
    }

    void save() {
        std::ofstream outfile("external_db.txt");
        if (!outfile) {
            printf("文件在另一进程中已打开\n");
            exit(1);
        }

        for (auto it = data.begin(); it != data.end(); ++it) {
            string key = it->first;
            Extend save = it->second;

            outfile << key << "\t";
            outfile << save.name << "\t" << save.regex;
            outfile << "\n";
        }

        outfile.close();
    }

    void put(string key, Extend ext) {
        if (contains(key)) {
            data.at(key) = ext;
        }
        else {
            data.insert({ key, ext });
        }
    }

    bool contains(string key) {
        return data.count(key) > 0;
    }

    Extend get(string key) {
        return data.at(key);
    }

    void del(string key) {
        data.erase(key);
    }

    void setVal(vector<string> vals) {
        if (vals.size() == 0 || length() == 0) {
            return;
        }
        int i = 0;
        for (auto it = data.begin(); it != data.end(); ++it) {
            it->second.val = vals[i];
            i++;
        }
    }

    int length() {
        return data.size();
    }

    string getVals() {
        string str;
        int i = 0;
        for (auto it = data.begin(); it != data.end(); ++it) {
            str += it->second.val;
            if (i != length() - 1) str += "\t";
            i++;
        }
        return str;
    }

    map<string, Extend> getData() {
        return data;
    }
};