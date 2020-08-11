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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e5+1;
ll f[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	f[0] = 0;
	f[1] = 1;
	for(int i=2;i<N;i++) {
		f[i] = min(INFLL, f[i-1]+f[i-2]);
	}

	int n; ll k;
	cin >> n >> k;
	while(n > 2) {
		if(k <= f[n-2]) {
			n -= 2;
		} else {
			k -= f[n-2];
			n -= 1;
		}
	}
	if(n == 1) cout << "N" << nl;
	else cout << "A" << nl;

	return 0;
}
