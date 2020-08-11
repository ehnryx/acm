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
		int dumb, n;
		cin >> dumb >> n;
		cout << dumb << " ";

		int a[n], b[n];
		for(int i=0; i<n; i++) {
			cin >> a[i];
			b[i] = a[i];
		}
		sort(b, b+n);
		int match = 0;
		for(int i=0, j=0; i<n; i++) {
			while(j < n && b[i] != a[j]) {
				j++;
			}
			match += (j < n);
			j++;
		}
		cout << n - match << nl;
	}

	return 0;
}
