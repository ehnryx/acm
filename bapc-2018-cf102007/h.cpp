//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Edge {
	ll v, c;
	bool operator < (const Edge& o) const {
		return c > o.c;
	}
};

const int N = 1e5 + 1;
vector<Edge> adj[N];
int deg[N];
ll fast[N], slow[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m, s, t;
	cin >> n >> m >> s >> t;
	for(int i=0; i<m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[b].push_back({a, c});
		deg[a]++;
	}

	memset(fast, INF, sizeof fast);
	priority_queue<Edge> fbfs;
	queue<int> sbfs;
	fbfs.push({t, 0});
	sbfs.push(t);

	while(!fbfs.empty() || !sbfs.empty()) {
		if(!sbfs.empty()) {
			int u = sbfs.front();
			sbfs.pop();
			for(auto [v, c] : adj[u]) {
				fbfs.push({v, slow[u] + c});
			}
		} else {
			auto [u, d] = fbfs.top();
			fbfs.pop();
			if(fast[u] < INFLL) continue;
			fast[u] = d;
			for(auto [v, c] : adj[u]) {
				slow[v] = max(slow[v], fast[u] + c);
				if(--deg[v] == 0) {
					sbfs.push(v);
				}
			}
		}
	}

	if(deg[s]) {
		cout << "infinity" << nl;
	} else {
		cout << slow[s] << nl;
	}

	return 0;
}
