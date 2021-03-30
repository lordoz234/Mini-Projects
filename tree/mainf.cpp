#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <regex>
#include <unordered_set>
#include <string>
#include <map>
#include <iomanip>
#include <sstream>
#include <cassert>
#include <time.h>
#include <numeric>
#include <complex>

using namespace std;
using ull = unsigned long long;
using ll = long long;
using ld = long double;
using D = double;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;

#define pb push_back
#define mp make_pair
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define makeunique(x) sort(all(x)), (x).resize(unique(all(x)) - (x).begin())
#define rep(i, x)  for(int i = 0; i < (x); i++)
#define rrep(i, x) for(int i = (x - 1); i >= 0; i--)
#define sqrt(x) sqrt(abs(x))
#define y1 y1_1234413
#define j1 j1_235
#define y0 y0_235
#define j0 j0_256
#define fi first
#define se second
#define re return
#define prev PREV
#define sz(x) ((int)x.size())

template<typename T> T sqr(T a) { re a * a; }
template<typename T> T gcd(T a, T b) { re b ? gcd(b, a % b) : a; }
template<typename T> T sgn(T a) { re a > 0 ? 1 : (a < 0 ? -1 : 0); }
template<typename T> T abs(T a) { re a > 0 ? a : -a; }

const ld st = 0.000001;
const ld pi = acos((ld)-1);

#define FILENAME ""

const ll MAXN = 1000000 + 10;

struct node {
    int data;
    node *left;
    node *right;
    node *parent;
};

class tree {
public:
    class iterator;
    node *root;
    tree();
    void insert(int x);
    node* creates(int x, node *v);
    void insert1(node *v, int x);
    bool find(int x);
    node* erases(node* v, int x);
    void bfs();
    void dfs(node *v);
    void dfs();
    int extract_max();
    int extract_min();
    node* next (int v);
    node* minimum(node *v);
    
    iterator begin() {
        node *temp = root;
        while (temp != nullptr) {
            if (temp -> left == nullptr) {
                break;
            }
            temp = temp -> left;
        }
        return temp;
    }
    iterator end() {
        return nullptr;
    }
    
    class iterator {
    public:
        typedef iterator self_type;
        typedef node* value_type;
        typedef node*& reference;
        typedef node** pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;
        node* tr;
        node*curent;
        stack <node*> stk;
        iterator(node* v)
        {
            tr = v;
            curent = v;
            if (stk.size() == 0) {
                curent = nullptr;
                node* temp = tr;
                vector <node*> l;
                while (temp != nullptr) {
                    l.push_back(temp);
                    temp = temp -> parent;
                }
                for (int j = l.size() - 1; j >= 1; j--) {
                    stk.push(l[j]);
                }
            }
        }
        node* operator++(int) {
            while (curent != NULL || !stk.empty()) {
                if (curent != NULL) {
                    stk.push(curent);
                    curent = curent->left;
                } else {
                    node *ret = stk.top();
                    stk.pop();
                    curent = ret->right;
                    tr = ret;
                    return ret;
                }
            }
            tr = nullptr;
            return nullptr;
        }
        bool operator == (const iterator& i) {
            return tr == i.tr;
        }
        bool operator != (const iterator& i) {
            return tr != i.tr;
        }
    };
};

tree::tree() {
    root = nullptr;
}

node* tree::creates(int x, node *v) {
    node *temp = new node();
    temp -> data = x;
    temp -> left = nullptr;
    temp -> right = nullptr;
    temp -> parent = v;
    return temp;
}

void tree::insert (int x) {
    node* temp = nullptr;
    if (root == nullptr) {
        root = temp;
    } else {
        node *s = root;
        while (s != nullptr) {
            if (s -> data > x) {
                if (s -> left == nullptr) {
                    s -> left = temp;
                    break;
                }
                s = s -> left;
            } else {
                if (s -> right == nullptr) {
                    s -> right = temp;
                    break;
                }
                s = s -> right;
            }
        }
    }
}

void tree::insert1(node *v, int x) {
    if (v == nullptr) {
        root = creates(x, nullptr);
    }
    else if (x > v -> data) {
        if (v -> right == nullptr) {
            v -> right = creates(x, v);
            return;
        }
        insert1(v -> right, x);
    }
    else {
        if (v -> left == nullptr) {
            v -> left = creates(x, v);
            return;
        }
        insert1(v -> left, x);
    }
}

node* tree::next (int v) {
    node* temp =  root;
    node* s = nullptr;
    while (temp != nullptr) {
        if (temp -> data > v) {
            s = temp;
            temp = temp -> left;
        }
        else {
            temp = temp -> right;
        }
    }
    return s;
}

bool tree::find (int x) {
    node *s = root;
    while (s != nullptr) {
        if (s -> data > x) {
            if (s -> left == nullptr) {
                return false;
            }
            s = s -> left;
        } else if (s -> data < x) {
            if (s -> right == nullptr) {
                return false;
            }
            s = s -> right;
        } else {
            return true;
        }
    }
    return false;
}

node* tree::minimum(node *v) {
    if (v -> left == nullptr) {
        return v;
    }
    return minimum(v -> left);
}

node* tree::erases (node *r, int x) {
    if (r == nullptr) return r;
    if (x < r -> data) {
        r -> left = erases (r -> left, x);
    }
    else if (x > r -> data) {
        r -> right = erases (r -> right, x);
    }
    else if (r -> left != nullptr && r -> right != nullptr) {
        r -> data = minimum(r -> right) -> data;
        r -> right = erases(r -> right, r -> data);
    }
    else {
        if (r -> left != nullptr) {
            r = r -> left;
        }
        else {
            r = r -> right;
        }
    }
    return r;
}

void tree::bfs () {
    queue <node *> q;
    q.push(root);
    while (!q.empty()) {
        node *v = q.front();
        cout << v -> data << " ";
        q.pop();
        if (v -> left != nullptr) {
            q.push(v -> left);
        }
        if (v -> right != nullptr) {
            q.push(v -> right);
        }
    }
}

void tree::dfs (node* v) {
    cout << v -> data << " ";
    if (v -> left != nullptr) {
        dfs(v -> left);
    }
    if (v -> right != nullptr) {
        dfs(v -> right);
    }
}

void tree::dfs () {
    stack <node *> q;
    q.push(root);
    while (!q.empty()) {
        node *v = q.top();
        cout << v -> data << " ";
        q.pop();
        if (v -> right != nullptr) {
            q.push(v -> right);
        }
        if (v -> left != nullptr) {
            q.push(v -> left);
        }
    }
}

int tree::extract_max() {
    node *s = root;
    while (s -> right != nullptr) {
        s = s -> right;
    }
    return s -> data;
}

int tree::extract_min() {
    node *s = root;
    while (s -> left != nullptr) {
        s = s -> left;
    }
    return s -> data;
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL), cout.tie(NULL);
    //    freopen("symposium.in", "r", stdin);
    //    freopen("symposium.out", "w", stdout);
    tree vl;
    vl.insert1(vl.root, 7);
    vl.insert1(vl.root, 5);
    vl.insert1(vl.root, 4);
    vl.insert1(vl.root, 10);
    vl.insert1(vl.root, 9);
    vl.insert1(vl.root, 100);
    vl.insert1(vl.root, 1);
    vl.insert1(vl.root, 233);
    vl.insert1(vl.root, 50);
    vl.insert1(vl.root, 23);
    vl.insert1(vl.root, 11);
    for (auto it = vl.begin(); it != vl.end(); it++) {
        cout << it.tr->data << " ";
    }
    re 0;
}
