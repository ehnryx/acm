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
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 50 + 1;
ll ncr[N][N];
ll p2[N];

ll choose(int n, int r) {
	if(r<0 || r>n) return 0;
	return ncr[n][r];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(int i=0; i<N; i++) {
		ncr[i][0] = ncr[i][i] = 1;
		for(int j=1; j<i; j++) {
			ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
		}
	}
	p2[0] = 1;
	for(int i=1; i<N; i++) {
		p2[i] = p2[i-1] * 2;
	}

	int T;
	cin >> T;
	while(T--) {
		int n, a, b, w;
		cin >> n >> a >> b >> w;
		int need = (n+2) / 2;
		if(n-b < need) {
			cout << "RECOUNT!" << nl;
			continue;
		}
		ll p = 0;
		for(int k=a; k<=n-b; k++) {
			if(k < need) continue;
			p += choose(n-a-b, k-a);
		}
		if(100 * p > w * p2[n-a-b]) {
			cout <<	"GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!" << nl;
		} else {
			cout << "PATIENCE, EVERYONE!" << nl;
		}
	}

	return 0;
}
