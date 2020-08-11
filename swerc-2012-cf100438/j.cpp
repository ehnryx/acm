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

map<ll,tuple<int,int,int,char>> dp[1<<6];

void solve(int bm, const vector<int>& a) {
	if(!dp[bm].empty()) return;
	if(__builtin_popcount(bm) == 1) {
		int i = __builtin_ctz(bm);
		dp[bm][a[i]] = make_tuple(0, 0, 0, 0);
		return;
	}

	for(int sm=(bm-1)&bm; sm; sm=(sm-1)&bm) {
		solve(sm, a);
		solve(bm^sm, a);
		for(const auto& it : dp[sm]) {
			ll x = it.first;
			for(const auto& jt : dp[bm^sm]) {
				ll y = jt.first;
				if(!dp[bm].count(x+y)) {
					dp[bm][x+y] = make_tuple(sm, x, y, '+');
				}
				if(x > y && !dp[bm].count(x-y)) {
					dp[bm][x-y] = make_tuple(sm, x, y, '-');
				}
				if(!dp[bm].count(x*y)) {
					dp[bm][x*y] = make_tuple(sm, x, y, '*');
				}
				if(x % y == 0 && !dp[bm].count(x/y)) {
					dp[bm][x/y] = make_tuple(sm, x, y, '/');
				}
			}
		}
	}
}

void print_moves(int bm, ll val) {
	if(__builtin_popcount(bm) == 1) return;
	auto [sm, x, y, op] = dp[bm][val];
	print_moves(sm, x);
	print_moves(bm^sm, y);
	cout << x << " " << op << " " << y << " = " << val << nl;
}

void score(vector<int> a, int goal) {
	for(int bm=0; bm<1<<6; bm++) {
		dp[bm].clear();
	}
	solve((1<<6) - 1, a);

	ll best = INFLL;
	vector<string> ans;
	for(int bm=1; bm<1<<6; bm++) {
		auto it = dp[bm].lower_bound(goal);
		if(it != dp[bm].end() && abs(it->first-goal) < abs(best-goal)) {
			best = it->first;
		}
		if(it != dp[bm].begin() && abs(prev(it)->first-goal) < abs(best-goal)) {
			best = prev(it)->first;
		}
	}

	for(int bm=1; bm<1<<6; bm++) {
		if(dp[bm].count(best)) {
			print_moves(bm, best);
			break;
		}
	}
	cout << "Best approx: " << best << nl;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while(T--) {
		vector<int> a(6);
		for(int i=0; i<6; i++) {
			cin >> a[i];
		}
		int goal;
		cin >> goal;
		cout << "Target: " << goal << nl;
		score( a, goal);
		cout << nl;
	}

	return 0;
}
