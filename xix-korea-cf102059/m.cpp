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

struct Edge {
	int id, cost;
};

struct Answer {
	int num;
	ll cost;
	Answer(int n=0, ll c=0): num(n), cost(c) {}
	void operator += (const Answer& o) {
		num += o.num; cost += o.cost;
	}
	Answer operator + (const Answer& o) {
		return Answer(num + o.num, cost + o.cost);
	}
};

const int N = 2.5e5+1;
vector<Edge> adj[N];

Answer dp[N][2]; // node, skip
Answer dfs(int u, bool skip, int p, ll c) {
	if (dp[u][skip].num != -1) return dp[u][skip];
	Answer base;
	Answer best;
	for (const Edge& e : adj[u]) {
		if (e.id != p) {
			Answer leave = dfs(e.id, false, u, c);
			Answer take = dfs(e.id, true, u, c);
			base += leave;
			ll diff = take.cost + e.cost+c - leave.cost;
			if (diff > best.cost || (diff == best.cost && take.num+1 > leave.num)) {
				best = { take.num + 1 - leave.num, diff };
			}
		}
	}
	if (skip) {
		return dp[u][skip] = base;
	} else {
		return dp[u][skip] = base + best;
	}
}

int count(ll c) {
	memset(dp, -1, sizeof dp);
	return dfs(1, false, 0, c).num;
}

void output(ll c, int k) {
	memset(dp, -1, sizeof dp);
	Answer ans = dfs(1, false, 0, c);
	if (ans.num < k) cout << "Impossible" << nl;
	else cout << ans.cost - (ll)c*k << nl;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, k;
	cin >> n >> k;

	for (int i=1; i<n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
	}

	ll left = -INFLL/n;
	ll right = INFLL/n;
	while (left < right) {
		ll sum = left+right;
		ll mid = (sum < 0 ? (sum-1)/2 : sum/2);
		if (count(mid) < k) {
			left = mid+1;
		} else {
			right = mid;
		}
	}
	output(left, k);

	return 0;
}
