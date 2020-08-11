#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9+7;

const int N = 300+1;
vector<int> adj[N];
ll b[N], par[N];
//map<ll,vector<vector<ll>>> part[N];
map<ll,vector<ll>> part[N];

void dfs(int u) {
	if (adj[u].empty()) {
		part[u][0] = { 0, inverse(b[u]) };
		part[u][b[u]] = { 1 };
		//part[u][0].push_back({ 0, inverse(b[u]) });
		//part[u][b[u]].push_back({ 1 });
	}

	else {
		for (int x : adj[u]) {
			dfs(x);
			for (const auto& it : part[x]) {
				if (part[u].count(it.first)) {
					part[u][it.first] = multiply(part[u][it.first], it.second);
				} else {
					part[u][it.first] = it.second;
				}
				part[u][it.first] = part[u]
				for (const auto& v : it.second) {
					part[u][it.first].push_back(v);
				}
			}
		}
		vector<ll> cur = { 1 };
		for (auto it = part[u].rbegin(); it != part[u].rend(); it++) {
			it->second = multiply(cur, it->second);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	for (int i=1; i<=n; i++) {
		cin >> b[i] >> par[i];
		adj[par[i]].push_back(i);
	}
	dfs(adj[0][0]);

	return 0;
}
