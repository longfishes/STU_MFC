#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include "Extend.h"

using namespace std;

class ExternalList {

    map<string, Extend> data;

public:

    string printHeaderOfFields() {
        return  "英文名\t\t中文名\t\t正则";
    }

    void show() {
        printHeaderOfFields();
        cout << "id\t\t" << "学号\t\t" << "^(20[0-9]{2})\\d{8}$" << "\t\t（系统预设字段）" << endl;
        cout << "name\t\t" << "姓名\t\t" << "^.*$" << "\t\t\t\t（系统预设字段）" << endl;
        cout << "gender\t\t" << "性别\t\t" << "^[0-2]$" << "\t\t\t\t（系统预设字段）" << endl;
        cout << "age\t\t" << "年龄\t\t" << "^([1-9][0-9]{1,2})$" << "\t\t（系统预设字段）" << endl;
        cout << "province\t" << "省份\t\t" << "^.*$" << "\t\t\t\t（系统预设字段）" << endl;
        cout << "major\t\t" << "专业\t\t" << "^.*$" << "\t\t\t\t（系统预设字段）" << endl;
        for (auto it = data.begin(); it != data.end(); ++it) {
            cout << it->first << "\t\t" << it->second.name << "\t\t" << it->second.regex << endl;
        }
        cout << endl;
    }

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

    string printHeader() {
        string s;
        for (auto it = data.begin(); it != data.end(); ++it) {
            s += it->second.name + "\t";
        }
        return s + "\n";
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

    void printVals() {
        cout << getVals() << endl;
    }

    map<string, Extend> getData() {
        return data;
    }

};