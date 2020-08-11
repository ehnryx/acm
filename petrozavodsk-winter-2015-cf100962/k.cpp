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

const int N = 2e5+1;
int degree[N];
vector<int> adj[N];
set<pii> edges;
bitset<N> vis;

bool dfs(int root, int cur, int par = -1) {
	if (vis[cur]) {
		if (cur != root && par != root) {
			return false;
		} else {
			return true;
		}
	}
	vis[cur] = true;

	for (int x : adj[cur]) {
		if (x != par) {
			if (!dfs(root, x, cur)) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;

	int a, b;
	for (int i=0; i<m; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
		degree[a]++;
		degree[b]++;
	}

	vector<int> sorted;
	for (int i=1; i<=n; i++) {
		sorted.push_back(degree[i]);
		if (degree[i] % 2 == 1) {
			cout << 0 << nl;
			return 0;
		}
	}
	sort(sorted.begin(), sorted.end(), greater<int>());

	if (sorted[0] == 2) { // all
		cout << n << nl;
		for (int i=1; i<=n; i++) {
			cout << i << " ";
		}
		cout << nl;
	}
	else if (sorted[0] == sorted[1]) { // two
		if (sorted[2] == 2) {
			cout << 2 << nl;
			for (int i=1; i<=n; i++) {
				if (degree[i] > 2) cout << i << " ";
			}
			cout << nl;
		} else {
			cout << 0 << nl;
		}
	}
	else { // one
		int ans = 0;
		for (int i=1; i<=n; i++) {
			if (degree[i] == sorted[0]) ans = i;
		}
		if (dfs(ans, ans)) {
			cout << 1 << nl;
			cout << ans << nl;
		} else {
			cout << 0 << nl;
		}
	}

	return 0;
}
