#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const char nl = '\n';

int n, m;

const int N = 2e5 + 1;
int X[N], Y[N], R[N];
vector<int> adj[N];
int par[N];
bool have[N];

int bx;
struct Int {
	int i; bool t;
	Int(int _i, bool _t): i(_i), t(_t) {}
	ld val() const {
		ld h = sqrt((ld)R[i]*R[i] - (ld)(bx-X[i])*(bx-X[i]));
		return Y[i] + (t ? h : -h);
	}
	bool operator < (const Int& o) const {
		ld v = val();
		ld ov = o.val();
		if(v != ov) return v < ov;
		else return t < o.t;
	}
};

int dp[N][2];
int solve(int u, int t) {
	if(dp[u][t] != -1) return dp[u][t];
	int sum0 = 0;
	int sum1 = 0;
	for(int v : adj[u]) {
		sum0 += solve(v, 0);
		sum1 += solve(v, 1);
	}
	if(t == 0) {
		if(u <= n) {
			dp[u][t] = sum1;
		} else {
			dp[u][t] = sum0;
		}
	} else {
		if(u <= n) {
			dp[u][t] = max(sum1, 1 + sum0);
		} else {
			dp[u][t] = sum1;
		}
	}
	return dp[u][t];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m;
	vector<pair<int,int>> p;
	for(int i=1; i<=n+m; i++) {
		cin >> X[i] >> Y[i] >> R[i];
		p.push_back(make_pair(X[i]-R[i], i));
		p.push_back(make_pair(X[i]+R[i], i));
	}
	sort(p.begin(), p.end());

	set<Int> cur;
	for(const auto& [x, i] : p) {
		bx = x;
		if(have[i]) {
			auto it = cur.lower_bound(Int(i,0));
			cur.erase(cur.erase(it));
		} else {
			have[i] = true;
			cur.insert(Int(i,1));
			auto it = cur.insert(Int(i,0)).first;
			if(it != cur.begin()) {
				--it;
				if(it->t == 0) {
					adj[it->i].push_back(i);
					par[i] = it->i;
				} else {
					adj[par[it->i]].push_back(i);
					par[i] = par[it->i];
				}
			}
		}
	}

	memset(dp, -1, sizeof dp);
	for(int i=n+1; i<=n+m; i++) {
		cout << max(solve(i, 1), 1 + solve(i, 0)) << nl;
	}

	return 0;
}
