#include <string>
#include <map>
#include "ExternalList.h"

using namespace std;

class Student {

public:

    string name;

    int gender = 0;

    int age = 0;

    string province;

    string major;

    ExternalList elist;

public:

    string toString() {
        string s_gender;
        string s_age;
        if (name.empty()) {
            name = "";
        }
        if (gender == 1) {
            s_gender = "男";
        }
        else if (gender == 2) {
            s_gender = "女";
        }
        else {
            s_gender = "";
        }
        if (age > 0) {
            s_age = to_string(age);
        }
        else {
            s_age = "";
        }
        if (province.empty()) {
            province = "";
        }
        if (major.empty()) {
            major = "";
        }

        return name + "\t" + s_gender + "\t" + s_age + "\t" + province + "\t" + major + "\t" + elist.getVals();
    }

};