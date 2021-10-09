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



int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(2);

	ld r, h, d1, a1, d2, a2;
	while(cin >> r >> h >> d1 >> a1 >> d2 >> a2) {
		ld dif = min(abs(a1-a2), 360 - abs(a1-a2));
		ld R = sqrt(r*r + h*h);
		ld A = dif * r/R;
		cout << sqrt(d1*d1 + d2*d2 - 2*d1*d2*cos(A*M_PIl/180)) << nl;
	}

	return 0;
}
