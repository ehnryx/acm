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



//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	bool first = true;
	for (int n;;) {
		cin >> n;
		if (!n) break;

		if (!first) {
			cout << nl;
		}
		first = false;

		string _;
		getline(cin,_);

		string grid[n];
		int height = 0;
		for (int i=0; i<n; i++) {
			getline(cin,grid[i]);
			height = max(height, (int)grid[i].size());
		}

		for (int i=0; i<n; i++) {
			while (grid[i].size() < height) {
				grid[i].push_back(' ');
			}
		}

		for (int i=0; i<height; i++) {
			for (int j=0; j<n; j++) {
				if (grid[j][i] == ' ') {
					grid[j][i] = '.';
				} else {
					break;
				}
			}
			for (int j=n-1; j>=0; j--) {
				if (grid[j][i] == '+' || grid[j][i] == ' ') cout << grid[j][i];
				else if (grid[j][i] == '-') cout << '|';
				else if (grid[j][i] == '|') cout << '-';
			}
			cout << nl;
		}
	}

	return 0;
}
