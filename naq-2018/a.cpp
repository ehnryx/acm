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

const int N = 100+1;
int grid[N][5][5];

set<int> nowin(int r, const set<int>& s, const set<int>& o, bool& ok) {
	ok = true;
	for (int i=0; i<5; i++) {
		bool win = true;
		set<int> ocnt;
		for (int j=0; j<5; j++) {
			if (!s.count(grid[r][i][j])) {
				win = false;
				break;
			}
			if (o.count(grid[r][i][j])) {
				ocnt.insert(grid[r][i][j]);
			}
		}
		if (win) {
			return ocnt;
		}
	}
	set<int> bad;
	ok = false;
	return bad;
}

bool valid(int n, int a, int b) {
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			set<int> s, o;
			for (int k=0; k<5; k++) {
				s.insert(grid[a][i][k]);
			}
			for (int k=0; k<5; k++) {
				if (s.count(grid[b][j][k])) o.insert(grid[b][j][k]);
				else s.insert(grid[b][j][k]);
			}
			if (s.size() < 10) {
				bool ok = false;
				for (int r=1; r<=n; r++) {
					if (r==a||r==b) continue;
					set<int> cur = nowin(r, s, o, ok);
					if (ok) {
						for (auto it = o.begin(); it != o.end(); ) {
							if (cur.count(*it)) it++;
							else it = o.erase(it);
						}
					}
				}
			}
			if (!o.empty()) {
				return true;
			}
		}
	}
	return false;
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

	for (int r=1; r<=n; r++) {
		for (int i=0; i<5; i++) {
			for (int j=0; j<5; j++) {
				cin >> grid[r][i][j];
			}
		}
	}

	for (int i=1; i<=n; i++) {
		for (int j=i+1; j<=n; j++) {
			if (valid(n,i,j)) {
				cout << i << " " << j << nl;
				return 0;
			}
		}
	}

	cout << "no ties" << nl;

	return 0;
}
