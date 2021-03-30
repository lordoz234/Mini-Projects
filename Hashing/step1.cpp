#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

#define pb push_back
#define fi first
#define se second
using namespace std;

struct info {
    string Sex;
    string Age;
    string Female;
    info (string _Sex, string _Age, string _Female):Sex(_Sex), Age(_Age), Female(_Female){}
    info() = default;
    friend bool operator<(info &a, info &b);
    friend bool operator>(info &a, info &b);
    friend bool operator==(info &a, info &b);
    friend bool operator!=(info &a, info &b);
};

bool operator<(info &a, info &b) {
    return a.Age < b.Age;
}

bool operator>(info &a, info &b) {
    return a.Age < b.Age;
}

bool operator==(info &a, info &b) {
    return a.Age == b.Age;
}

bool operator!=(info &a, info &b) {
    return a.Age != b.Age;
}

struct Node {
    string data;
    info man;
    Node *left;
    Node *right;
    Node *parent;
};

class CSVReader
{
    std::string fileName;
    std::string delimeter;
    
public:
    CSVReader(std::string filename, std::string delm = ",") :
    fileName(filename), delimeter(delm)
    { }
    
    // Function to fetch data from a CSV File
    std::vector<std::vector<std::string> > getData();
};

/*
 * Parses through csv file line by line and returns the data
 * in vector of vector of strings.
 */
std::vector<std::vector<std::string> > CSVReader::getData()
{
    std::ifstream file(fileName);
    
    std::vector<std::vector<std::string> > dataList;
    
    std::string line = "";
    // Iterate through each line and split the content using delimeter
    while (getline(file, line))
    {
        std::vector<std::string> vec;
        boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
        dataList.push_back(vec);
    }
    // Close the File
    file.close();
    
    return dataList;
}

class Hashing {
public:
    vector <Node*> a;
    long long m;
    Hashing(long long _m);
    long long Hash_func(string s);
    void insert(string x, info people);
    vector <info> find(string x);
    void deletes(string x);
};

Hashing::Hashing(long long _m) {
    m = _m;
    a.resize(m + 1);
}

long long Hashing::Hash_func(string s) {
    int p = 31;
    long long p_pow = 1, ans = 0;
    for (int i = 0; i < s.size(); i++) {
        ans += ((int)s[i])*p_pow;
        p_pow *= p;
        p_pow = p_pow % m;
        if (ans >= m) {
            ans -= m;
        }
    }
    return ans % m;
}

void Hashing::insert(string x, info people) {
    long long h = Hash_func(x);
    Node *root = a[h];
    if (root == nullptr) {
        Node *temp = new Node();
        temp -> data = x;
        temp -> man = people;
        temp -> right = nullptr;
        temp -> left = nullptr;
        temp -> parent = nullptr;
        a[h] = temp;
    }
    else {
        while (root != nullptr) {
            if (root -> data <= x) {
                if (root -> right == nullptr) {
                    Node *temp = new Node();;
                    temp -> data = x;
                    temp -> man = people;
                    temp -> right = nullptr;
                    temp -> left = nullptr;
                    temp -> parent = root;
                    root -> right = temp;
                    break;
                }
                else {
                    root = root -> right;
                }
            }
            else {
                if (root -> left == nullptr) {
                    Node *temp = new Node();;
                    temp -> data = x;
                    temp -> man = people;
                    temp -> right = nullptr;
                    temp -> left = nullptr;
                    temp -> parent = root;
                    root -> left = temp;
                    break;
                }
                else {
                    root = root -> left;
                }
            }
        }
    }
}

vector <info> Hashing::find (string x) {
    long long h = Hash_func(x);
    Node *root = a[h];
    vector <info> ans;
    while (root != nullptr) {
        if (root -> data < x) {
            root = root -> right;
        } 
        else if (root -> data > x) {
            root = root -> left;
        }
        else {
            ans.pb(root -> man);
            root = root -> right;
        }
    }
    return ans;
}

void Hashing::deletes (string x) {
    long long h = Hash_func(x);
    Node *root = a[h];
    while (root != nullptr) {
        if (root -> data < x) {
            root = root -> right;
        } 
        else if (root -> data > x) {
            root = root -> left;
        }
        else {
            if (root -> right == nullptr) {
                if (root -> parent -> left-> data == x) {
                    root -> parent -> left = root -> left;
                }
                else {
                    root -> parent -> right = root -> left;
                }
            }
            else if (root -> right != nullptr && root -> right -> left == nullptr) {
                if (root -> parent -> left -> data == x) {
                    root -> parent -> left = root -> right;
                }
                else {
                    root -> parent -> right = root -> right;
                }
            }
            else {
                if (root -> parent -> left-> data == x) {
                    root -> parent -> left = root -> right -> left;
                }
                else {
                    root -> parent -> right = root -> right -> left;
                }
            }
            delete root;
        }
    }
}
int main() {
    CSVReader reader("/Users/vladislavdevlikamov/Downloads/_ea07570741a3ec966e284208f588e50e_titanic (1).csv");
    std::vector<std::vector<std::string> > dataList = reader.getData();
    Hashing t(1024);
    for (std::vector <std::string> vec : dataList) {
        string name;
        for (int i = 0; i < vec[3].size(); i++) {
            if (vec[3][i] >= 'a' && vec[3][i] <= 'z') name += vec[3][i];
            else if (vec[3][i] >= 'A' && vec[3][i] <= 'Z') name += vec[3][i];
        }
        string female;
        for (int i = 0; i < vec[4].size(); i++) {
            if (vec[4][i] >= 'a' && vec[4][i] <= 'z') female += vec[4][i];
            else if (vec[4][i] >= 'A' && vec[4][i] <= 'Z') female += vec[4][i];
            else if (vec[4][i] == '.') female += vec[4][i];
        }
        info mans(vec[5], vec[6], female);
        t.insert(name, mans);
    }
    cout << "Write name: " << "\n";
    string name;
    cin >> name;
    vector <info> temp = t.find(name);
    if (temp.size() == 0) {
        cout << "Not found" << "\n";
    }
    for (int i = 0; i < temp.size(); i++) {
          cout << name << " " << temp[i].Female << " " << temp[i].Sex << " " << temp[i].Age << "\n";
    }
    t.deletes(name);
    vector <info> temp1 = t.find(name);
    if (temp1.size() == 0) {
        cout << "Not found" << "\n";
    }
    for (int i = 0; i < temp1.size(); i++) {
          cout << name << " " << temp1[i].Female << " " << temp1[i].Sex << " " << temp1[i].Age << "\n";
    }
    return 0;
}