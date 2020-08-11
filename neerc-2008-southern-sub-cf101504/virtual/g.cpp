#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 55;

vector<int> adj[N];
bool vis[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n, x; cin >> n >> x;
	for (int i = 0; i < N; i++) {
		int d; cin >> d;
		for (int j = 0; j < d; j++) {
			int k; cin >> k;
			adj[i].push_back(k-1);
		}
	}
	set<int> ans;
	queue<pair<int, int>> q;
	q.emplace(x-1, 0);
	vis[x-1] = 1;
	while (!q.empty()) {
		int u, d; tie(u, d) = q.front(); q.pop();
		if (d == 2) ans.insert(u);
		else if (d > 2) break;
		for (int v : adj[u]) {
			if (!vis[v]) {
				vis[v] = 1;
				q.emplace(v, d+1);
			}
		}
	}
	cout << ans.size() << nl;
	for (int i : ans) cout << i+1 << nl;

	return 0;
}
