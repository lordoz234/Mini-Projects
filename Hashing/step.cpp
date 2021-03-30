#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <cmath>

using namespace std;
 
long long error = 0, rope = 0;

class HashTable {
public:
    HashTable();
    vector <vector <string> > temp;
    void insert(const string&s, const string&s1);
    void insert1(const string&s, const string&s1);
    long long hash_func(const string&s);
    long long hash_func1(const string&s);
    long long hash_func2(const string&s);
    void print();
    void check(const int n);
};              

HashTable::HashTable() {
    temp.resize(1024);
}

long long HashTable::hash_func(const string&s) {
    const int p = 23;
    long long hash = 0, p_pow = 1;
    for (int i = 0; i < s.size(); i++) {
        hash += (s[i] + 1) * p_pow;
        p_pow *= p;
        p_pow %= 1000000007;
        if (hash >= 1024) {
            hash -= 1024;
        }
    }
    return hash % 1024;
}

long long HashTable::hash_func1(const string&s) {
    long long ans = 0;
    for (int i = 5; i < s.size(); i++) {
        ans += (pow(10, 6 - (i - 5)))*(s[i] - '0');
    }
    return ans % 1024;
}

long long HashTable::hash_func2(const string&s) {
    long long ans1 = 0;
    long long A = 655360001;
    long long w = pow(2, 31);
    long long M = pow(2, 0);
    long long ans = 0;
    for (int i = 5; i < s.size(); i++) {
        ans += (pow(10, 6 - (i - 5)))*(s[i] - '0');
    }
    ans1 = (M*((A*ans/w))) % 1024;
    return ans1;
}


void HashTable::insert(const string&s, const string&s1) {
    if (temp[hash_func(s)].size() != 0) {
        if (temp[hash_func1(s)].size() != 0) {
            if (temp[hash_func2(s)].size() != 0) {
                temp[hash_func2(s)].push_back(s1);
                rope = max(rope, (long long)temp[hash_func2(s)].size());
                error++;
            }
            else {
                temp[hash_func2(s)].push_back(s1);
                rope = max(rope, (long long)temp[hash_func2(s)].size());
            }
        }
        else {
            temp[hash_func1(s)].push_back(s1);
            rope = max(rope, (long long)temp[hash_func1(s)].size());
        }
    }
    else {
        temp[hash_func(s)].push_back(s1);
        rope = max(rope, (long long)temp[hash_func(s)].size());
    }
}

void HashTable::insert1(const string&s, const string&s1) {
    if (temp[hash_func1(s)].size() != 0) {
        error++;
    }
    temp[hash_func1(s)].push_back(s1);
    rope = max(rope, (long long)temp[hash_func1(s)].size());
}

void HashTable::print() {
    for (int i = 0; i < temp.size(); i++) {
        for (int j = 0; j < temp[i].size(); j++) {
            cout << temp[i][j] << " ";
        }
        cout << endl;
    }
}

string f() {
    string h = "89";
    for (int i = 0; i < 6; i++) {
        char m = ((rand() % 10) + '0');
        h += m;
    }
    return h;
}

int main() {
    HashTable tr;
    for (int i = 0; i < 1000011; i++) {
        char t = i;
        string sr = "vl";
        sr += t;
        tr.insert(f(), sr);
    }
    cout << error << endl;
    cout << rope << endl;
    return 0;
}