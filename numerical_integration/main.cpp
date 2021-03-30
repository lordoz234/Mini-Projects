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
#include <random>
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
#define next next
#define sz(x) ((int)x.size())
 
template<typename T> T sqr(T a) { re a * a; }
template<typename T> T gcd(T a, T b) { re b ? gcd(b, a % b) : a; }
template<typename T> T sgn(T a) { re a > 0 ? 1 : (a < 0 ? -1 : 0); }
template<typename T> T abs(T a) { re a > 0 ? a : -a; }
 
const ld st = 0.000001;
const ld pi = acos((ld)-1);
const int mod = 1000000033;

const ll inf = 2000000000000;
 
 
#define FILENAME ""

using namespace std;

double f (double x) {
	return x*x*sin(x);
}

double left_rectangle (int n, double a, double b) {
	double h = (b - a)/(double) n;
	double x = a;
	double ans = 0;
	for (int i = 0; i < n; i++) {
		ans += f(x);
		x += h;
	}
	ans *=(b - a)/(double) n;
	return ans;
}

double right_rectangle (int n, double a, double b) {
	double h = (b - a)/(double) n;
	double x = b;
	double ans = 0;
	for (int i = 0; i < n; i++) {
		ans += f(x);
		x -= h;
	}
	ans *=(b - a)/(double) n;
	return ans;
}

double middle_rectangle (int n, double a, double b) {
	double h = (b - a)/(double) n;
	double x = a;
	double ans = 0;
	for (int i = 0; i < n; i++) {
		ans += f((2*x + h)/2.0);
		x += h;
	}
	ans *=(b - a)/(double) n;
	return ans;
}

double trapezoid (int n, double a, double b) {
	double h = (b - a)/(double) n;
	double x = a;
	double ans = 0;
	for (int i = 0; i < n; i++) {
		ans += (f(x) + f(x + h))/2.0*h;
		x += h;
	}
	return ans;
}

double simpsons_method (int n, double a, double b) {
	double h = (b - a)/(double) n;
	double x = a;
	double ans = 0;
	for (int i = 0; i < n; i++) {
		ans += (f(x) + 4*f((2*x + h)/2.0) + f(x + h))*h/6.0;
		x += h;
	}
	return ans;
}

double gauss (int n, double a, double b) {
	double h = (b - a)/(double) n;
	double x = a;
	double ans = 0;
	for (int i = 0; i < n; i++) {
		ans += (f((2*x + h)/2.0 - (h/(2*sqrt(3)))) + f((2*x + h)/2.0 + (h/(2*sqrt(3)))))*h/2.0;
		x += h;
	}
	return ans;
}

double simpsons_1 (int n, double a, double b) {
	double h = (b - a)/(double) n;
	double x = a;
	double ans = 0;
	for (int i = 0; i < n; i++) {
		ans += f(x) * ((i==0 || i==n) ? 1 : ((i&1)==0) ? 2 : 4);
		x += h;
	}
	return ans*h/3.0;
}

double ff (double x, double a, double b, double n) {
	return ((b - a)/n)*x + a;
}

double monte_carlo (int n, double a, double b) {
	std::default_random_engine generator;
 	std::uniform_int_distribution<int> distribution(0,n);
 	double ans = 0;
 	for (int i = 0; i < n; i++) {
 		//cout << ff(distribution(generator), a, b, n) << endl;
 		ans += f(ff(distribution(generator), a, b, n));
 	}
 	return ans*(b - a)/(double) n;
}

int main() {
   ios::sync_with_stdio(0);
    cin.tie(NULL), cout.tie(NULL);
    double ans = 2.246239104913078824873274671944929147363584885727986496010;
    cout << fixed << setprecision(10);
    cout << abs(ans - left_rectangle(1000000, 1, 2)) << endl;
    cout << abs(ans - right_rectangle(1000000, 1, 2)) << endl;
    cout << abs(ans - middle_rectangle(1000000, 1, 2)) << endl;
    cout << abs(ans - trapezoid(1000000, 1, 2)) << endl;
    cout << abs(ans - simpsons_method(1000000, 1, 2)) << endl;
    cout << abs(ans - gauss(1000000, 1, 2)) << endl;
    cout << abs(ans - simpsons_1(1000000, 1, 2)) << endl;
    cout << abs(ans - monte_carlo(1000000, 1, 2)) << endl;
}   