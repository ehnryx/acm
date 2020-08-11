//#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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

ll stick(ll a, ll n) {
	return n*a + n*(n-1)/2;
}

const int N = 1e5+1;
int par[N], deg[N], h[N];
unordered_set<int> level[N];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	ll n, s;
	cin >> n >> s;

	if (s == n*(n+1)/2) {
		cout << "Yes" << nl;
		for (int i=2; i<=n; i++) {
			cout << i-1 << ' ';
		}
		cout << nl;
		return 0;
	}

	ll lb, ub;
	int k;
	for (k=2; k<n; k++) {
		ub = k + stick(k+1, n-k);
		lb = 0;
		ll cur = n;
		for (ll t=1; cur>0; cur-=t, t*=k) {
			lb += cur;
		}
		if (lb <= s && s <= ub) {
			break;
		}
	}
	cerr << "precompute: " << k << " w/ " << lb << " " << ub << endl;

	if (k==n) {
		cout << "No" << nl;
		return 0;
	}

	priority_queue<int> nxt;

	h[1] = 0;
	for (int i=2; i<=n-k; i++) {
		deg[i-1] = 1;
		par[i] = i-1;
		h[i] = h[par[i]]+1;
	}
	deg[n-k] = k;
	for (int i=n-k+1; i<=n; i++) {
		par[i] = n-k;
		h[i] = h[par[i]]+1;
		nxt.push(i);
	}

	for (int i=1; i<=n; i++) {
		if (deg[i] < k) {
			level[h[i]].insert(i);
		}
	}

	cerr << "moves needed: " << ub-s << endl;
	while (ub > s) {
		assert(!nxt.empty());
		int cur = nxt.top();

		if (deg[cur] == 0 && h[cur] >= 2 && !level[h[cur]-2].empty()) {
			ub--;
			int pp = *level[h[cur]-2].begin();
			deg[pp]++;
			if (deg[pp] == k) level[h[pp]].erase(pp);
			deg[par[cur]]--;
			if (deg[par[cur]] < k) level[h[par[cur]]].insert(par[cur]);
			if (deg[par[cur]] == 0 && par[cur] != 1) {
				nxt.push(par[cur]);
			}
			level[h[cur]].erase(cur);
			par[cur] = pp;
			h[cur] = h[pp]+1;
			level[h[cur]].insert(cur);
		}
		else {
			nxt.pop();
		}
	}

	cout << "Yes" << nl;
	for (int i=2; i<=n; i++) {
		cout << par[i] << ' ';
	}
	cout << nl;

	return 0;
}
