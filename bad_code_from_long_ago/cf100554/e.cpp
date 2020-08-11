#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<int> pt;
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
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ ";
	for (const T& it : v) os << it << " ";
	os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ ";
	for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
	os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

pt com[512*512+1];
int grid[513][513];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;
	while (T--) {
		memset(grid, 0, sizeof grid);

		int n;
		cin >> n;

		if (n % 2 == 0) {
			for (int j = 0; j < n; j += 2) {
				for (int i = 1; i <= 2*n; i++) {
					if (i % 4 == 2 || i % 4 == 3)
						com[j*n + i] = pt(0,1);
					else
						com[j*n + i] = pt(0,-1);
				}

				if (j % 4 == 2) {
					com[j*n + 2*n] = 1;
					if (j != 0) {
						for (int i = 1; i <= 3; i++)
							com[j*n + i] *= -1;
						com[j*n + 4] = 1;
					}
				}
				
				if (j % 4 == 0) {
					com[j*n + 1] = 1;
					if (j != n-2) {
						for (int i = 2*n-2; i <= 2*n; i++)
							com[j*n + i] *= -1;
						com[j*n + 2*n-3] = 1;
					}
				}
			}
		}

		else {
			int mid = 1;
			for (int i = 2; i <= 2*n; i += 4)
				mid += i;

			int shift = -4;
			int diff = 2*n;
			for (int j = 0; j <= n*n; j += diff, diff += shift) {
				//cerr << j << " " << diff << " " << shift << nl;
				if (shift == 0) shift = 4;
				else if (diff == 2) shift = 0;

				for (int i = 1; i <= diff; i++) {
					if (i % 4 == 2 || i % 4 == 3)
						com[j + i - (shift>0)] = pt(0,1);
					else
						com[j + i - (shift>0)] = pt(0,-1);
				}
				com[j] = 1;
			}
		}

		com[1] = 1;
		pt pos = pt(1,1);
		pt dir = pt(1,0);
		for (int i = 1; i <= n*n; i++) {
			//cerr << i << ": " << pos;
			grid[pos.real()][pos.imag()] = i;
			dir *= com[i];
			//cerr << " , " << dir << " , " << com[i] << nl;
			pos += dir;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cout << grid[i][j] << " ";
			}
			cout << nl;
		}
	}

	return 0;
}
