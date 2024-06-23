#include "Student.h"
#include <map>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool containsString(const std::string& haystack, const std::string& needle) {
    return haystack.find(needle) != std::string::npos;
}

class StudentList {

    map<string, Student> data;

    ExternalList elist;

public:

    void loads() {
        data.clear();
        ifstream temp("db.txt");
        if (!temp.good()) {
            temp.close();
            ofstream outfile("db.txt");
            outfile << "200000000001	张三	1	19	广东省	软件    tt\n";
            outfile << "200000000003	李四	2	20	广东省	软件    new\n";
            outfile.close();
        }
        ifstream file("db.txt");
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
                Student save;
                if (fields.size() < 6) {
                    throw "exp";
                }
                string id = fields[0];
                save.name = fields[1];
                save.gender = stoi(fields[2]);
                save.age = stoi(fields[3]);
                save.province = fields[4];
                save.major = fields[5];

                elist.loads();
                vector<string> vals;
                for (int i = 6; i < fields.size(); i++) {
                    vals.push_back(fields[i]);
                }
                elist.setVal(vals);
                save.elist = elist;

                put(id, save);
            }
            catch (...) {

            }
        }
        file.close();
    }

    void save() {
        std::ofstream outfile("db.txt");
        if (!outfile) {
            printf("文件在另一进程中已打开\n");
            exit(1);
        }

        for (auto it = data.begin(); it != data.end(); ++it) {
            string id = it->first;
            Student save = it->second;

            outfile << id << "\t";
            outfile << save.name << "\t" << save.gender << "\t" << save.age << "\t" << save.province << "\t" << save.major << "\t";
            outfile << save.elist.getVals();
            outfile << "\n";
        }

        outfile.close();
    }

    void put(string id, Student stu) {
        if (contains(id)) {
            data.at(id) = stu;
        }
        else {
            data.insert({ id, stu });
        }
    }

    bool contains(string id) {
        return data.count(id) > 0;
    }

    Student get(string id) {
        return data.at(id);
    }

    void del(string id) {
        data.erase(id);
    }

    string printHeader() {
        string s;
        elist.loads();
        s += "学号\t\t姓名\t性别\t年龄\t省份\t专业\t";
        s += elist.printHeader();
        return s;
    }

    void print() {
        printHeader();
        for (auto it = data.begin(); it != data.end(); ++it) {
            std::cout << it->first << "\t" << it->second.toString() << "\t" << endl;
        }
        cout << endl;
    }

    string printOne(string id) {
        string s;
        if (!contains(id)) {
            return "查询的学生不存在！";
        }
        else {
            s += printHeader();
            s += id + "\t" + get(id).toString();
        }
        return s;
    }

    void printSearch(string name) {
        printHeader();
        for (auto it = data.begin(); it != data.end(); ++it) {
            string id = it->first;
            Student result = it->second;
            if (containsString(result.name, name)) {
                cout << id << "\t" << get(id).toString() << endl;
            }
        }
        cout << endl;
    }

    void setDefaultVal(string key, string name, string regex) {
        for (auto it = data.begin(); it != data.end(); ++it) {
            Extend ext = Extend(name, regex);
            ext.val = "null";
            it->second.elist.put(key, ext);
        }
    }

    void delVals(string key) {
        for (auto it = data.begin(); it != data.end(); ++it) {
            it->second.elist.del(key);
        }
    }

    map<string, Student> getData() {
        return data;
    }

    ExternalList getElist() {
        return elist;
    }

};