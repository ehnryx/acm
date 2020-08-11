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

	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;
		vector<char> ans(n);
		int s[m];
		string t[m];
		for(int i=0; i<m; i++) {
			cin >> s[i] >> t[i];
			--s[i];
		}

		bool ok = true;
		for(int i=0; i<m && ok; i++) {
			if(t[i].find('*') == -1) {
				if(n - s[i] != t[i].size()) {
					ok = false;
					break;
				}
				for(int j=0; j<t[i].size(); j++) {
					if(ans[s[i]+j]) {
						ok &= (ans[s[i]+j] == t[i][j]);
					} else {
						ans[s[i]+j] = t[i][j];
					}
				}
			} else {
				if(n - s[i] < (int)t[i].size() - 1) {
					ok = false;
					break;
				}
				for(int j=0; t[i][j]!='*'; j++) {
					if(ans[s[i]+j]) {
						ok &= (ans[s[i]+j] == t[i][j]);
					} else {
						ans[s[i]+j] = t[i][j];
					}
				}
				for(int j=(int)t[i].size()-1; t[i][j]!='*'; j--) {
					if(ans[n-((int)t[i].size()-j)]) {
						ok &= (ans[n-((int)t[i].size()-j)] == t[i][j]);
					} else {
						ans[n-((int)t[i].size()-j)] = t[i][j];
					}
				}
			}
		}

		for(int i=0; i<n; i++) {
			ok &= !!ans[i];
		}

		if(ok) {
			for(int i=0; i<n; i++) {
				cout << ans[i];
			}
			cout << nl;
		} else {
			cout << "IMPOSSIBLE" << nl;
		}
	}

	return 0;
}
