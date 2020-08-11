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
unordered_set<int> adj[N];
int vis[N];

void init() {
	memset(vis, -1, sizeof vis);
}

#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	init();

	int n;
	cin >> n;

	int a, b;
	for (int i=1; i<n; i++) {
		cin >> a >> b;
		adj[a].insert(b);
		adj[b].insert(a);
	}

	int cnt = 0;
	while (cnt < n) {
		for (int i=1; i<=n; i++) {
			if (adj[i].empty()) {
				if (vis[i] == -1) vis[i] = 1;
			}
			else if (adj[i].size() == 1) {
				int par = *adj[i].begin();
				if (vis[i] != -1) {
					adj[par].erase(i);
					adj[i].clear();
				}
				else {
					vis[par] = 1;
					for (int x : adj[par]) {
						if (vis[x] == -1) vis[x] = 0;
						adj[x].erase(par);
					}
					adj[par].clear();
				}
			}
		}

		cnt = 0;
		for (int i=1; i<=n; i++) {
			if (vis[i] != -1) cnt++;
		}
	}

	for (int i=1; i<=n; i++) {
		cout << vis[i] << " ";
	}
	cout << nl;

	return 0;
}
