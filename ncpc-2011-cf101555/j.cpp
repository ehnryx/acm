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

const int N = 1e5+1;
vector<int> adj[N];
int ans[N];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, m;
	cin >> n >> m;

	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	while (clock() < 0.618*CLOCKS_PER_SEC) {
		for (int i = 1; i <= n; i++) {
			int same = 0;
			for (int j : adj[i]) {
				same += ans[i] == ans[j];
			}
			if (same > 1) {
				ans[i] ^= 1;
			}
		}
	}

	int bm = 0;
	for (int i = 1; i <= n; i++) {
		bm |= 1<<ans[i];
	}

	if (__builtin_popcount(bm) == 1) {
		cout << 1 << nl;
		for (int i = 1; i <= n; i++) {
			cout << i << " ";
		}
		cout << nl;
	}
	else {
		cout << 2 << nl;
		for (int i = 1; i <= n; i++) {
			if (ans[i]) cout << i << " ";
		}
		cout << nl;
		for (int i = 1; i <= n; i++) {
			if (!ans[i]) cout << i << " ";
		}
		cout << nl;
	}

	return 0;
}
