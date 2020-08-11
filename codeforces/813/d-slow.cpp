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

const int N = 5e3 + 1;
int a[N], m[N];
int dp[N][N], single[N];

const int M = 1e5 + 2;
vector<int> idx[M], mod[7];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> a[i];
		m[i] = a[i]%7;
		mod[m[i]].push_back(i);
		idx[a[i]].push_back(i);
	}

	function<vector<int>(int,int)> get_nxt = [=](int i, int lb) {
		if(i == 0) return lb+1 <= n ? vector<int>(1, lb+1) : vector<int>(0);
		vector<int> nxt;
		auto it = upper_bound(mod[m[i]].begin(), mod[m[i]].end(), lb);
		if(it != mod[m[i]].end()) nxt.push_back(*it);
		it = upper_bound(idx[a[i]+1].begin(), idx[a[i]+1].end(), lb);
		if(it != idx[a[i]+1].end()) nxt.push_back(*it);
		it = upper_bound(idx[a[i]-1].begin(), idx[a[i]-1].end(), lb);
		if(it != idx[a[i]-1].end()) nxt.push_back(*it);
		return nxt;
	};

	for(int i=1; i<=n; i++) {
		single[i] = max(single[i], 1);
		for(int ni : get_nxt(i, i)) {
			single[ni] = max(single[ni], single[i] + 1);
		}
	}

	int ans = 0;
	for(int i=1; i<=n; i++) {
		vector<int> nxti = get_nxt(i, i);
		for(int j=1; j<i; j++) {
			dp[i][j] = max(dp[i][j], single[j] + 1);
			vector<int> nxtj = get_nxt(j, i);
			for(int ni : nxti) {
				dp[ni][j] = max(dp[ni][j], dp[i][j] + 1);
			}
			for(int nj : nxtj) {
				dp[nj][i] = max(dp[nj][i], dp[i][j] + 1);
			}
			ans = max(ans, dp[i][j]);
		}
	}
	cout << ans << nl;

	return 0;
}
