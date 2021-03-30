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
#define rall(x) x.rbegin(), x.rend
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
#define next NEXT
#define sz(x) ((int)x.size())
#define FOR(i,a,n) for (int i=(a);i<(n);++i)
#define MEMS(a, b) memset(a, b, sizeof(a))

template<typename T> T sqr(T a) { re a * a; }
template<typename T> T gcd(T a, T b) { re b ? gcd(b, a % b) : a; }
template<typename T> T sgn(T a) { re a > 0 ? 1 : (a < 0 ? -1 : 0); }
template<typename T> T abs(T a) { re a > 0 ? a : -a; }

const int inf = 2e9;
const ld st = 0.000001;
const ld pi = acos((ld)-1);
const int MAXN = 200001;
const int mod = 1e9 + 7;


#define FILENAME ""

int maxlog = 20;
vector <vector <int>> g;
vector <int> h;
int par[10000][20];

void dfs (int v, int t, int he) {
    par[v][0] = t;
    for (int i = 1; i < maxlog; i++) {
        par[v][i] = par[par[v][i - 1]][i - 1];
    }
    h[v] = he;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (to != t) {
            dfs(to, v, he + 1);
        }
    }
}

int up (int v, int d) {
    for (int i = maxlog - 1; i >= 0; i--) {
        if (d >= (1 << i)) {
            d -= (1 << i);
            v = par[v][i];
        }
    }
    re v;
}

int lca (int a, int b) {
    if (h[a] < h[b]) {
        swap(a, b);
    }
    a = up(a, h[a] - h[b]);
    if (a == b) re a;
    for (int i = maxlog - 1; i >= 0; i--) {
        if (par[a][i] != par[b][i]) {
            a = par[a][i];
            b = par[b][i];
        }
    }
    re par[a][0] + 1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    g.resize(n);
    h.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        g[x].pb(y);
        g[y].pb(x);
    }
    dfs(0, 0, 0);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        cout << lca(a, b) << endl;
    }
    return 0;
}
