#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int M = 1e6+2;
const int N = 500+1;
vector<int> idx[N];
int v[M], a[M];
int l[N], r[N];
int minv[2*N][2*N];
ll dp[2*N][2*N];

ll solve(int m, int s, int e) {
	if (s > e) return 1;
	if (dp[s][e] != -1) return dp[s][e];
	int x = minv[s][e];
	assert(x > 0);
	ll res = 0;
	for (int j=r[x]; j>=s && a[j]>=x; j=l[a[j]]-1) {
		int lid = l[a[j]];
		for (int k=l[x]; k<=e && a[k]>=x; k=r[a[k]]+1) {
			int rid = r[a[k]];
			ll left = solve(m, s, lid-1);
			ll right = solve(m, rid+1, e);
			ll mid = solve(m, lid, l[x]-1) * solve(m, r[x]+1, rid) % MOD;
			res += left * right % MOD * mid % MOD;
		}
	}
	return dp[s][e] = res % MOD;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;
	int id = 0;
	FOR(i,1,m) {
		cin >> v[i];
		if (v[i] != a[id]) {
			a[++id] = v[i];
			idx[v[i]].push_back(id);
		}
	}
	m = id;

	FOR(i,1,m) {
		if (!l[a[i]]) l[a[i]] = i;
		r[a[i]] = i;
	}

	FOR(i,1,n) {
		FOR(j,1,i-1) {
			if ((l[i]<l[j] && l[j]<r[i]) || (l[i]<r[j] && r[j]<r[i])) {
				cout << 0 << nl;
				return 0;
			}
		}
	}

	assert(m < 2*N);
	FOR(i,1,m) {
		FOR(j,1,i) {
			minv[j][i] = INF;
			FOR(k,j,i) {
				minv[j][i] = min(minv[j][i], a[k]);
			}
		}
	}

	memset(dp, -1, sizeof dp);
	cout << solve(m, 1, m) << nl;

	return 0;
}
