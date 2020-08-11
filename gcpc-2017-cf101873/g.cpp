#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(a*conj(b)); }
ld area(const pol& v) {
	ld s = 0; int n = v.size();
	for (int i = n-1, j = 0; j < n; i = j++) s += cp(v[i], v[j]);
	return abs(s)/2;
}

ll border(const pt& a, const pt& b) {
	ll x = abs(llround(a.real() - b.real()));
	ll y = abs(llround(a.imag() - b.imag()));
	return __gcd(x,y);
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n;
	cin >> n;

	int a, b;
	vector<pt> p;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		p.push_back(pt(a,b));
	}

	ld A, B;
	A = area(p);
	B = 0;
	for (int i = 0; i < n; i++) {
		B += border(p[i], p[(i+1)%n]);
	}

	cout << llround(A+1-B/2) << nl;

	return 0;
}
