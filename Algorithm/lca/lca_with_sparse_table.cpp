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
vector <pair<int, int>> lst;
int ind[10000];
pair<int, int> tab[10000][20];

void dfs (int v, int t, int he) {
    ind[v] = lst.size();
    lst.pb(mp(he, v));
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (to != t) {
            dfs(to, v, he + 1);
            lst.pb(mp(he, v));
        }
    }
}

void build () {
    for (int i = 0; i < maxlog; i++) {
        for (int j = 0; j <= sz(lst) - (1 << i); j++) {
            if (i == 0) {
                tab[j][i] = {lst[j].fi, lst[j].se};
            }
            else {
                if (tab[j][i - 1].fi < tab[j + (1 << (i - 1))][i - 1].fi) {
                    tab[j][i] = tab[j][i - 1];
                }
                else {
                    tab[j][i] = tab[j + (1 << (i - 1))][i - 1];
                }
            }
        }
    }
}

int log2 (int a) {
    re log(a)/log(2);
}

int lca (int l, int r) {
    l = ind[l];
    r = ind[r];
    if (l > r) {
        swap(l, r);
    }
    int d = log2(r - l + 1);
    if (tab[l][d].fi < tab[r - (1 << d) + 1][d].fi) {
        re tab[l][d].se;
    }
    else {
        re tab[r - (1 << d) + 1][d].se;
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        g[x].pb(y);
        g[y].pb(x);
    }
    dfs(0, 0, 0);
    build();
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        cout << lca(a, b) + 1 << endl;
    }
    return 0;
}