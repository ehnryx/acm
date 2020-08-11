#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const char nl = '\n';
const ll MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;

unsigned long long k1, k2;

unsigned long long xorShift128Plus() {
	unsigned long long k3 = k1, k4 = k2;
	k1 = k4;
	k3 ^= k3 << 23;
	k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
	return k2 + k4;
}

ll inv(ll b) {
	int e = MOD-2; ll ans = 1, cur = b;
	while (e) {
		if (e%2) ans *= cur, ans %= MOD;
		cur *= cur, cur %= MOD;
		e /= 2;
	}
	return ans;
}

void pivot(vector<vector<ll>>& a, int r, int c) {
	int m = a.size(), n = a[0].size(); ll tmp = a[r][c];
	for (int i = 0; i < n; i++) a[r][i] = a[r][i] * inv(tmp) % MOD;
	for (int i = 0; i < m; i++) if (i != r) { ll k = a[i][c];
		for (int j = 0; j < n; j++) a[i][j] = (MOD+a[i][j]-(a[r][j]*k)%MOD)%MOD; }
}
ll det(vector<vector<ll>> a) {
	int n = a.size(), j; ll ret = 1;
	for (int i = 0; i < n; i++) {
		for (j = i; j < n; j++) if (a[j][i] != 0) {
			if (j != i) { a[j].swap(a[i]); ret = MOD - ret; }
			ret = (ret * a[i][i]) % MOD; pivot(a, i, i);
			break;
		}
		if (j == n) return 0;
	}
	return ret;
}

struct edge {
	int u, v; unsigned long long w;
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T; cin >> T;
	while (T--) {
		int n, m; cin >> n >> m >> k1 >> k2;
		vector<unordered_map<ull, vector<edge>>> adj(n);
		map<ull, vector<edge>> edges;
		vector<int> uf(n); iota(uf.begin(), uf.end(), 0);
		function<int(int)> find = [&](int x) -> int {
			return x == uf[x] ? x : uf[x] = find(uf[x]);
		};
		auto merge = [&](int a, int b) {
			uf[find(a)] = find(b);
		};
		for (int i = 0; i < m; i++) {
			int u = xorShift128Plus() % n;
			int v = xorShift128Plus() % n;
			ull w = xorShift128Plus();
			adj[u][w].push_back(edge{u, v, w});
			adj[v][w].push_back(edge{v, u, w});
			edges[w].push_back(edge{u, v, w});
		}
		ll wgt = 0;
		for (const auto& p : edges) {
			for (const edge& e : p.second) {
				if (find(e.u) != find(e.v)) {
					wgt = (wgt+p.first%MOD)%MOD;
					merge(e.u, e.v);
				}
			}
		}

		ll num = 1;
		iota(uf.begin(), uf.end(), 0);
		for (const auto& p : edges) {
			map<int, int> active;
			int id = 0;
			for (const edge& e : p.second) {
				if (find(e.u) == find(e.v)) continue;
				if (!active.count(find(e.u))) {
					active[find(e.u)] = id++;
				}
				if (!active.count(find(e.v))) {
					active[find(e.v)] = id++;
				}
			}
			vector<int> uf2(active.size()); iota(uf2.begin(), uf2.end(), 0);
			//if (uf2.size()) cerr << uf2.size() << " " << active.size() << nl;
			function<int(int)> find2 = [&](int x) -> int {
				//cerr << "find2 " << x << " " << uf2.size() << nl;
				return x == uf2[x] ? x : uf2[x] = find2(uf2[x]);
			};
			auto merge2 = [&](int a, int b) {
				uf2[find2(a)] = find2(b);
			};
			for (const auto& e : p.second) {
				if (find(e.u) == find(e.v)) continue;
				merge2(active[find(e.u)], active[find(e.v)]);
			}
			vector<vector<int>> comps(active.size());
			for (const auto& p : active) {
				comps[find2(p.second)].push_back(p.second);
			}
			vector<vector<vector<ll>>> mats(active.size());
			for (int i = 0; i < active.size(); i++) {
				if (comps[i].empty()) continue;
				mats[i] = vector<vector<ll>>(comps[i].size(), vector<ll>(comps[i].size()));
				map<int, int> compinv;
				for (int j = 0; j < comps[i].size(); j++) {
					compinv[comps[i][j]] = j;
				}
				for (const edge& e : p.second) {
					if (!compinv.count(active[find(e.u)])) continue;
					mats[i][compinv[active[find(e.u)]]][compinv[active[find(e.v)]]]--;
					mats[i][compinv[active[find(e.v)]]][compinv[active[find(e.u)]]]--;
					mats[i][compinv[active[find(e.u)]]][compinv[active[find(e.u)]]]++;
					mats[i][compinv[active[find(e.v)]]][compinv[active[find(e.v)]]]++;
				}
				num = num * det(mats[i]) % MOD;
			}
			for (const edge& e : p.second) {
				merge(e.u, e.v);
			}
		}

		cerr << wgt << " " << num << nl;
		cout << wgt * num % MOD << nl;
	}

	return 0;
}
