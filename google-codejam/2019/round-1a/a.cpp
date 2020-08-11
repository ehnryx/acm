#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}
template <class T> 
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}
template <class T> 
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) os << it << " "; 
	return os << '}';
}
template <class T, class U> 
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ "; for (const pair<T,U>& it : v) os << it << " ";
	return os << '}';
}

////////////////////////////////////////////////////////////////////////

void solve();
void init() {
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	int T;
	cin >> T;
	for (int cc = 1; cc <= T; cc++) {
		cout << "Case #" << cc << ": ";
		solve();
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

// n > m
void solve1(int n, int m) {
	//cerr << "SOLVE 1" << nl;
	if (m == 2) {
		if (n < 5) cout << "IMPOSSIBLE" << nl;
		else {
			cout << "POSSIBLE" << nl;
			for (int i=0; i<n; i++) {
				cout << 1 + (i+2)%n << " " << 1 << nl;
				cout << 1 + i << " " << 2 << nl;
			}
		}
	} else {
		cout << "POSSIBLE" << nl;
		if (m%2 == 0 && n == m) {
			for (int i=0; i<n-1; i++) {
				for (int j=0; j<m; j++) {
					cout << 1 + (i+2*(j%2))%n << " " << 1 + j << nl;
				}
			}
			for (int i=n-1, j=0; j<m; j+=2) {
				cout << 1 + (i+2*((j+1)%2))%n << " " << 1 + j+1 << nl;
				cout << 1 + (i+2*((j)%2))%n << " " << 1 + j << nl;
			}
		} else {
			for (int i=0; i<n; i++) {
				for (int j=0; j<m; j++) {
					cout << 1 + (i+2*(j%2))%n << " " << 1 + j << nl;
				}
			}
		}
	}
}

// n <= m
void solve2(int n, int m) {
	//cerr << "SOLVE 2" << nl;
	if (n == 2) {
		if (m < 5) cout << "IMPOSSIBLE" << nl;
		else {
			cout << "POSSIBLE" << nl;
			for (int j=0; j<m; j++) {
				cout << 1 << " " << 1 + (j+2)%m << nl;
				cout << 2 << " " << 1 + j << nl;
			}
		}
	} else {
		cout << "POSSIBLE" << nl;
		if (n%2 == 0 && n == m) {
			for (int j=0; j<m-1; j++) {
				for (int i=0; i<n; i++) {
					cout << 1 + i << " " << 1 + (j+2*(i%2))%m << nl;
				}
			}
			for (int j=m-1, i=0; i<n; i+=2) {
				cout << 1 + i+1 << " " << 1 + (j+2*((i+1)%2))%m << nl;
				cout << 1 + i << " " << 1 + (j+2*((i)%2))%m << nl;
			}
		} else {
			for (int j=0; j<m; j++) {
				for (int i=0; i<n; i++) {
					cout << 1 + i << " " << 1 + (j+2*(i%2))%m << nl;
				}
			}
		}
	}
}

void caseinit() {
}

void solve() {
	caseinit();

	int n, m;
	cin >> n >> m;

	if (n == 3 && m == 3) {
		cout << "IMPOSSIBLE" << nl;
	} else {
		if (n > m) {
			solve1(n,m);
		} else {
			solve2(n,m);
		}
	}

	return;
}

