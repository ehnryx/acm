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
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

vector<vector<int>> bad =  {
	{12, 15, 10,  2},
	{ 6,  9, 11, 16},
	{ 3,  5,  1,  8},
	{ 4,  7, 14, 13},
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	if(n < 3) {
		cout << -1 << nl;
	} else if(n == 3) {
		vector<vector<int>> g = {
			{4, 2, 3},
			{7, 1, 9},
			{8, 5, 6},
		};
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				cout << g[i][j] << " ";
			}
			cout << nl;
		}
	} else {
		int g[n][n];
		for(int i=0; i<4; i++) {
			for(int j=0; j<4; j++) {
				g[n-4+i][n-4+j] = bad[i][j] + n*n-16;
			}
		}
		for(int k=0, cur=1; k<n-4; k++) {
			if(k%2 == 0) {
				g[n-2][k] = cur++;
				g[n-1][k] = cur++;
				for(int i=n-3; i>=k; i--) {
					g[i][k] = cur++;
				}
				for(int j=k+1; j<=n-3; j++) {
					g[k][j] = cur++;
				}
				g[k][n-1] = cur++;
				g[k][n-2] = cur++;
			} else {
				g[k][n-2] = cur++;
				g[k][n-1] = cur++;
				for(int j=n-3; j>=k; j--) {
					g[k][j] = cur++;
				}
				for(int i=k+1; i<=n-3; i++) {
					g[i][k] = cur++;
				}
				g[n-1][k] = cur++;
				g[n-2][k] = cur++;
			}
		}
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				cout << g[i][j] << " ";
			}
			cout << nl;
		}
	}

	return 0;
}
