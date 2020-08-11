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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;
	vector<string> g(n);
	for(int i=0; i<n; i++) {
		cin >> g[i];
	}

	vector<vector<bool>> good(n, vector<bool>(m));
	for(int i=1; i<n; i++) {
		for(int j=1; j<m; j++) {
			if(g[i-1][j] == g[i][j-1]) {
				good[i][j] = true;
			}
		}
	}

	int lb = m;
	bool ok = false;
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			if(good[i][j]) {
				ok |= j > lb;
			}
		}
		for(int j=0; j<m; j++) {
			if(good[i][j]) {
				lb = min(lb, j);
			}
		}
	}

	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			ok |= (i>0 && good[i][j] && good[i-1][j]);
			ok |= (j>0 && good[i][j] && good[i][j-1]);
		}
	}

	if(ok) cout << "YES" << nl;
	else cout << "NO" << nl;

	return 0;
}
