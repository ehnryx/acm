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



// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	string s;
	cin >> s;
	s = "R" + s;

	vector<int> g(n+1);
	for(int i=0; i<n; i++) {
		if(i > 0 && s[i] == s[i-1]) {
			g[i] = g[i-1] + 1;
		} else {
			g[i] = 1;
		}
	}

	for(int i=0; i<n; i++) {
		if(i+1 == n || s[i] != s[i+1]) {
			g[i-g[i]+1] = g[i];
		}
	}

	int cur = 0;
	for(int i=0; i<n; i++) {
		if(i+1 == n || s[i] != s[i+1]) {
			if(s[i] == 'R') {
				for(int j=1; j<g[i]; j++) {
					cout << cur + j << nl;
				}
				cout << cur + g[i] + g[i+1] << nl;
				cur += g[i] + g[i+1];
			} else {
				for(int j=1; j<=g[i]; j++) {
					cout << cur - j << nl;
				}
			}
		}
	}

	return 0;
}
