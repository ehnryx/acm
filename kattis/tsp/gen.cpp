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
	cout << fixed << setprecision(4);

	int n;
	cin >> n;
	vector<int> x = {7, 7, 999993, 999993};
	vector<int> y = {7, 999993, 7, 999993};
	cout << n << nl;
	for(int i=0; i<4; i++) {
		for(int j=0; j<n/4; j++) {
			ld a = x[i] + ((int)(rng()%200001) - 100000) / (ld)30000;
			ld b = y[i] + ((int)(rng()%200001) - 100000) / (ld)30000;
			cout << a << " " << b << nl;
		}
	}

	return 0;
}
