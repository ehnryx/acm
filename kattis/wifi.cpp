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
	cout << fixed << setprecision(1);

	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;
		int a[m];
		for(int i=0; i<m; i++) {
			cin >> a[i];
		}
		sort(a, a+m);
		ld l = 0;
		ld r = a[m-1];
		while(r-l > 1e-2) {
			ld v = (l+r) / 2;
			int cnt = 0;
			ld ub = -INF;
			for(int i=0; i<m; i++) {
				if(a[i] > ub) {
					ub = a[i] + 2*v;
					cnt++;
				}
			}
			if(cnt <= n) {
				r = v;
			} else {
				l = v;
			}
		}
		cout << r << nl;
	}

	return 0;
}
