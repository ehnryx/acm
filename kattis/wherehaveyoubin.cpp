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

const int N = 150 + 1;
const int M = 5;
int cnt[M], add[M], del[M];
int cost[N];
int dp[N][1<<M];
int memo[M][N][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	map<char,int> idx;
	idx['A'] = 0;
	idx['E'] = 1;
	idx['I'] = 2;
	idx['O'] = 3;
	idx['U'] = 4;

	string s;
	cin >> s;
	int n = s.size();
	for(int i=0; i<n; i++) {
		cin >> cost[i];
		if(s[i] != 'X') {
			cnt[idx[s[i]]]++;
		}
	}

	int m;
	cin >> m;
	for(int i=0; i<m; i++) {
		int v;
		cin >> v;
		--v;
		cnt[idx[s[v]]]--;
		del[idx[s[v]]]++;
		s[v] = 'X';
	}

	string t;
	cin >> t;
	if(t != "X") {
		for(char c : t) {
			add[idx[c]]++;
			cnt[idx[c]]++;
		}
	}

	memset(memo, -1, sizeof memo);
	function<int(int,int,int)> calc = [&] (int v, int l, int r) {
		if(memo[v][l][r] != -1) return memo[v][l][r];
		int move = cnt[v] - add[v];
		vector<int> vals;
		for(int i=0; i<l; i++) {
			if(s[i] != 'X' && idx[s[i]] == v) {
				vals.push_back(cost[i]);
			}
		}
		for(int i=r; i<n; i++) {
			if(s[i] != 'X' && idx[s[i]] == v) {
				vals.push_back(cost[i]);
			}
		}
		sort(vals.begin(), vals.end());
		int res = 0;
		for(int i=0; i<min(move,(int)vals.size()); i++) {
			res += vals[i];
		}
		return memo[v][l][r] = res;
	};

	memset(dp, INF, sizeof dp);
	dp[0][0] = 0;
	for(int i=1; i<=n; i++) {
		for(int bm=0; bm<1<<M; bm++) {
			dp[i][bm] = min(dp[i][bm], dp[i-1][bm]);
			for(int j=0; j<M; j++) {
				if(!(bm & 1<<j) || cnt[j] > i) continue;
				dp[i][bm] = min(dp[i][bm], dp[i-cnt[j]][bm^1<<j] + calc(j, i-cnt[j], i));
			}
		}
	}
	cout << dp[n][0b11111] << nl;

	return 0;
}
