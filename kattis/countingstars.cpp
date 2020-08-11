//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 100 + 2;
char g[N][N];
int dsu[N*N];
int find(int i) {
	if(dsu[i] == -1) return i;
	return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
	if(find(i) != find(j)) {
		dsu[find(i)] = find(j);
	}
}
int get(int i, int j) {
	return i*N + j;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(int n, m, tt=1; cin >> n >> m; tt++) {
		cout << "Case " << tt << ": ";
		memset(dsu, -1, sizeof dsu);
		for(int i=1; i<=n; i++) {
			cin >> (g[i] + 1);
			for(int j=1; j<=m; j++) {
				if(g[i-1][j] == g[i][j]) {
					link(get(i-1, j), get(i, j));
				}
				if(g[i][j-1] == g[i][j]) {
					link(get(i, j-1), get(i, j));
				}
			}
		}
		int ans = 0;
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=m; j++) {
				ans += (g[i][j] == '-' && find(get(i, j)) == get(i, j));
			}
		}
		cout << ans << nl;
	}

	return 0;
}
