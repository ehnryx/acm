#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;




int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int a, b;
	cin >> a >> b;

	if (a == 1 || b == 1) {
		cout << 0 << nl;
	}
	
	else if (a % 2 == 0) {
		cout << a*b/2 - 1 << nl;
		for (int i = 1; i < a; i++) {
			if (i % 4 == 1) {
				for (int j = 1; j < b; j++) {
					cout << i << " " << j << nl;
				}
			} else if (i % 4 == 3) {
				for (int j = b-1; j > 0; j--) {
					cout << i << " " << j << nl;
				}
			} else if (i % 4 == 0) {
				cout << i << " " << 1 << nl;
			} else {
				cout << i << " " << b-1 << nl;
			}
		}
	}

	else if (b % 2 == 0) {
		cout << a*b/2 - 1 << nl;
		for (int i = 1; i < b; i++) {
			if (i % 4 == 1) {
				for (int j = 1; j < a; j++) {
					cout << j << " " << i << nl;
				}
			} else if (i % 4 == 3) {
				for (int j = a-1; j > 0; j--) {
					cout << j << " " << i << nl;
				}
			} else if (i % 4 == 0) {
				cout << 1 << " " << i << nl;
			} else {
				cout << a-1 << " " << i << nl;
			}
		}
	}

	else {
		cout << (a*b-1)/2 - 1 << nl;
		if (a % 4 == 1) {
			for (int i = 0; i < (b-3)/2; i++) {
				cout << a-1 << " " << b-1-2*i << nl;
			}
		} else {
			for (int i = 0; i < (b-3)/2; i++) {
				cout << a-1 << " " << 1+2*i << nl;
			}
		}
		for (int i = 1; i < a; i++) {
			if (i % 4 == 1) {
				for (int j = 1; j < b; j++) {
					cout << i << " " << j << nl;
				}
			} else if (i % 4 == 3) {
				for (int j = b-1; j > 0; j--) {
					cout << i << " " << j << nl;
				}
			} else if (i % 4 == 0) {
				cout << i << " " << 1 << nl;
			} else {
				cout << i << " " << b-1 << nl;
			}
		}
	}

	return 0;
}
