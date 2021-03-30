#pragma GCC optimize("Ofast")
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
#include <stdexcept>
#include <unordered_set>
#include <string>
#include <map>
#include <complex>
#include <iomanip>
#include <sstream>
#include <cassert>
#include <time.h>
#include <numeric>
#include <complex>
#include <functional>
#include <limits>
#include <numeric>
#include <cstdlib>
   
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
#define rall(x) x.rbegin(), x.rend()
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
   
template<typename T> T sqr(T a) { re a * a; }
template<typename T> T gcd(T a, T b) { re b ? gcd(b, a % b) : a; }
template<typename T> T sgn(T a) { re a > 0 ? 1 : (a < 0 ? -1 : 0); }
template<typename T> T abs(T a) { re a > 0 ? a : -a; }
   
const int inf = 2e9;
const ld st = 0.000001;
const double pi = acos(-1);
const int MAXN = 1000001;
const double EPS = 0.0001;
 
#define FILENAME ""

typedef complex<double> ftype;


template <class T>
vector <ftype> fft (vector <T> p, ftype w) {
	int n = p.size();
	if (n == 1) {
		return vector<ftype>(1, p[0]);
	}
	else {
		vector <T> AB[2];
		for (int i = 0; i < n; i++) {
			AB[i % 2].push_back(p[i]);
		}
		auto A = fft(AB[0], w*w);
		auto B = fft(AB[1], w*w);
		vector <ftype> res(n);
		ftype wt = 1;
		int k = n/2;
		for (int i = 0; i < n; i++) {
			res[i] = A[i % k] + wt*B[i % k];
			wt *= w;
		}
		return res;
	}
}

vector<ftype> evaluate (vector <int> p) {
	while (__builtin_popcount(p.size()) != 1) {
		p.push_back(0);
	}
	double temp = 2*pi/p.size();
	return fft(p, polar(1.0, temp));
}

vector <int> interpolate(vector<ftype> p) {
	int n = p.size();
	double temp = 2*pi/n;
	auto inv = fft(p, polar(1.0, temp));
	reverse(inv.begin() + 1, inv.end());
	vector <int> res(n);
	for (int i = 0; i < n; i++) {
		res[i] = round(real(inv[i])/n);
	}
	return res;
}

void align(vector <int>& a, vector <int>&b) {
	int n = a.size() + b.size() - 1;
	while (a.size() < n) a.pb(0);
	while (b.size() < n) b.pb(0);
}

vector <int> poly_multiply (vector <int> a, vector <int> b) {
	align(a, b);
	auto A = evaluate(a);
	auto B = evaluate(b);
	for (int i = 0; i < A.size(); i++) {
		A[i] *= B[i];
	}
	return interpolate(A);
}

int main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0);    
    cin.tie(0);
  	int n, m;
  	cin >> n >> m;
  	vector <int> a, b;
  	for (int i = 0; i < n; i++) {
  		int x;
  		cin >> x;
  		a.pb(x);
  	}
  	for (int j = 0; j < m; j++) {
  		int x;
  		cin >> x;
  		b.pb(x);
  	}
  	auto res = poly_multiply(a, b);
  	ll ans = 0;
  	ll tt = n + m - 1;
  	for (int i = 0; i < res.size(); i++) {
  		ans += res[i]*pow(10, tt - i - 1);
  	}
  	cout << ans;
    return 0; 
}