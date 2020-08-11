#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int val[100];
vector<pii> edges;
int solve(int n, int u, int x, int m, int k) {
	if (u>n) {
		bool ok = true;
		for (const pii& e : edges) {
			if (val[e.first] == k && val[e.second] >= k) ok = false;
			if (val[e.second] == k && val[e.first] >= k) ok = false;
		}
		int cnt = 0;
		for (int i=1; i<=n; i++) {
			cnt += (val[i] == k);
		}
		return ok && (cnt<=x);
	}
	int res = 0;
	for (int j=1; j<=m; j++) {
		val[u] = j;
		res += solve(n, u+1, x, m, k);
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;
	for (int i=1; i<n; i++) {
		int a, b;
		cin >> a >> b;
		edges.push_back(pii(a,b));
	}
	int k, x;
	cin >> k >> x;
	cout << solve(n, 1, x, m, k) << nl;

	return 0;
}
