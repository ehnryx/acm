#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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



int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	const int M = 26;
	int p[M];
	for(int i=0; i<M; i++) {
		cin >> p[i];
		p[i]--;
	}

	string s, t;
	cin >> s >> t;
	int n = s.size();
	int m = t.size();

	const int N = 2e5;
	bitset<N> b[26], ans;

	for(int i=0; i<m; i++) {
		b[t[i]-'a'][i] = true;
	}

	ans.set();
	for(int i=0; i<n; i++) {
		ans &= (b[s[i]-'a'] | b[p[s[i]-'a']]) >> i;
	}

	for(int i=0; i+n<=m; i++) {
		cout << ans[i];
	}
	cout << nl;

	return 0;
}
