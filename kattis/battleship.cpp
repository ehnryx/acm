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

const int N = 42;
char a[N][N], b[N][N];
const int M = 2e3 + 1;
int x[M], y[M];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while(T--) {
		int n, m, k;
		cin >> m >> n >> k;
		for(int i=n-1; i>=0; i--) {
			for(int j=0; j<m; j++) {
				cin >> a[i][j];
			}
		}
		for(int i=n-1; i>=0; i--) {
			for(int j=0; j<m; j++) {
				cin >> b[i][j];
			}
		}
		for(int i=0; i<k; i++) {
			cin >> y[i] >> x[i];
		}

		bool A = true;
		bool B = true;
		for(int i=0; i<n; i++) {
			for(int j=0; j<m; j++) {
				if(a[i][j] == '#') {
					B = false;
				}
				if(b[i][j] == '#') {
					A = false;
				}
			}
		}

		for(int t=0; t<k && !A && !B; ) {
			while(t<k) {
				int i = x[t];
				int j = y[t];
				//cerr<<"one shoots @ "<<i<<" "<<j<<nl;
				++t;
				if(b[i][j] == '#') {
					b[i][j] = '_';
				} else {
					break;
				}
			}
			while(t<k) {
				int i = x[t];
				int j = y[t];
				//cerr<<"two shoots @ "<<i<<" "<<j<<nl;
				++t;
				if(a[i][j] == '#') {
					a[i][j] = '_';
				} else {
					break;
				}
			}

			A = true;
			B = true;
			for(int i=0; i<n; i++) {
				for(int j=0; j<m; j++) {
					if(a[i][j] == '#') {
						B = false;
					}
					if(b[i][j] == '#') {
						A = false;
					}
				}
			}
		}

		if(A == B) {
			cout << "draw" << nl;
		} else if(A) {
			cout << "player one wins" << nl;
		} else if(B) {
			cout << "player two wins" << nl;
		} else {
			assert(false);
		}

	}

	return 0;
}
