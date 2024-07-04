#include "Student.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// 定义二叉搜索树 BST 树根节点 数据结构
struct TreeNode {
    string key;
    Student value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string k, Student v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

class StudentList {

    TreeNode* root;
    ExternalList elist;

public:

    StudentList() : root(nullptr) {}

    ~StudentList() {
        clearTree(root);
    }

    void loads() {
        clearTree(root);
        root = nullptr;

        ifstream file("db.txt");
        if (!file.is_open() || file.peek() == ifstream::traits_type::eof()) {
            file.close();
            ofstream outfile("db.txt");
            if (!outfile) {
                cout << "Failed to create db.txt" << endl;
                return;
            }
            outfile << "200000000001\t张三\t1\t19\t广东省\t软件\ttt\n";
            outfile << "200000000003\t李四\t2\t20\t广东省\t软件\tnew\n";
            outfile.close();

            // Re-open file for reading after writing default data
            file.open("db.txt");
            if (!file.is_open()) {
                cout << "Failed to open db.txt after writing" << endl;
                return;
            }
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            vector<string> fields;
            string field;
            while (iss >> field) {
                fields.push_back(field);
            }

            try {
                if (fields.size() < 6) {
                    throw "Invalid data format";
                }

                string id = fields[0];
                Student save;
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
            catch (const char* msg) {
                cerr << "Error: " << msg << endl;
            }
        }

        file.close();
    }

    void save() {
        ofstream outfile("db.txt");
        if (!outfile) {
            cout << "Failed to open db.txt for writing" << endl;
            return;
        }

        saveTree(root, outfile);

        outfile.close();
    }

    void put(string id, Student stu) {
        root = insert(root, id, stu);
    }

    bool contains(string id) {
        return search(root, id) != nullptr;
    }

    Student get(string id) {
        TreeNode* node = search(root, id);
        if (node) {
            return node->value;
        }
        else {
            throw "Student not found";
        }
    }

    void del(string id) {
        root = remove(root, id);
    }

    void setDefaultVal(string key, string name, string regex) {
        setDefaultValues(root, key, name, regex);
    }

    void delVals(string key) {
        deleteValues(root, key);
    }

    map<string, Student> getData() {
        map<string, Student> result;
        collectData(root, result);
        return result;
    }

    ExternalList getElist() {
        return elist;
    }

private:

    // 二叉搜索树 BST 数据结构

    TreeNode* insert(TreeNode* node, string key, Student value) {
        if (node == nullptr) {
            return new TreeNode(key, value);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key, value);
        }
        else {
            node->value = value; // 更新存在的节点
        }

        return node;
    }

    TreeNode* search(TreeNode* node, string key) {
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return search(node->left, key);
        }
        else {
            return search(node->right, key);
        }
    }

    void saveTree(TreeNode* node, ofstream& outfile) {
        if (node != nullptr) {
            saveTree(node->left, outfile);

            outfile << node->key << "\t";
            Student save = node->value;
            outfile << save.name << "\t" << save.gender << "\t" << save.age << "\t" << save.province << "\t" << save.major << "\t";
            outfile << save.elist.getVals();
            outfile << "\n";

            saveTree(node->right, outfile);
        }
    }

    TreeNode* remove(TreeNode* node, string key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = remove(node->left, key);
        }
        else if (key > node->key) {
            node->right = remove(node->right, key);
        }
        else {
            // 找到要删除的节点
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // 拥有两个子节点的节点：获取中序遍历的后继节点（右子树中的最小节点）
            TreeNode* temp = minValueNode(node->right);

            // 将中序遍历的后继节点的内容复制到当前节点
            node->key = temp->key;
            node->value = temp->value;

            // 删除中序遍历的后继节点
            node->right = remove(node->right, temp->key);
        }

        return node;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void clearTree(TreeNode* node) {
        if (node != nullptr) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

    void setDefaultValues(TreeNode* node, string key, string name, string regex) {
        if (node != nullptr) {
            Extend ext = Extend(name, regex);
            ext.val = "*待填写*";
            node->value.elist.put(key, ext);

            setDefaultValues(node->left, key, name, regex);
            setDefaultValues(node->right, key, name, regex);
        }
    }

    void deleteValues(TreeNode* node, string key) {
        if (node != nullptr) {
            node->value.elist.del(key);
            deleteValues(node->left, key);
            deleteValues(node->right, key);
        }
    }

    void collectData(TreeNode* node, map<string, Student>& result) {
        if (node != nullptr) {
            collectData(node->left, result);
            result[node->key] = node->value;
            collectData(node->right, result);
        }
    }

};
