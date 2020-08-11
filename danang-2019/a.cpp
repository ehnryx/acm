#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
#define nl '\n'

const ll MOD = 1e9+7;

ll power(ll n, int e) {
	ll r = 1;
	for(;e;e/=2) {
		if(e&1) r = r*n % MOD;
		n = n*n % MOD;
	}
	return r;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;
		cout << power(3, n+m) * power(2, n*m) % MOD << nl;
	}

	return 0;
}
