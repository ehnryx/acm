#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
const int N = 500;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int c[N];
unordered_set<int> adj[N];
int v, e;
void init() {
	memset(c, 0, sizeof c);
	for (auto& s : adj) s.clear();
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	while (cin >> v >> e) {
		init();
		for (int i = 0; i < v; i++) {
			cin >> c[i];
		}
		for (int i = 0; i < e; i++) {
			int u, v; cin >> u >> v; u--; v--;
			adj[u].insert(v);
			adj[v].insert(u);
		}
		int ans = 0;
		// 1
		for (int i = 0; i < v; i++) {
			ans = max(ans, c[i]);
		}
		// 2
		for (int i = 0; i < v; i++) {
			for (int j : adj[i]) {
				ans = max(ans, c[i] + c[j]);
			}
		}
		// 3
		vector<vector<int>> tris;
		for (int i = 0; i < v; i++) {
			for (int j = i+1; j < v; j++) {
				for (int k = j+1; k < v; k++) {
					if (adj[i].count(j) && adj[i].count(k) && adj[j].count(k)) {
						tris.push_back({i, j, k});
						ans = max(ans, c[i] + c[j] + c[k]);
					}
				}
			}
		}
		// 4
		for (const auto& t : tris) {
			for (int i = 0; i < v; i++) {
				bool shit = 0;
				for (int j : t) {
					if (!adj[i].count(j)) {
						shit = 1;
						break;
					}
				}
				if (!shit) {
					ans = max(ans, c[t[0]] + c[t[1]] + c[t[2]] + c[i]);
				}
			}
		}
		cout << ans << nl;
	}

	return 0;
}
