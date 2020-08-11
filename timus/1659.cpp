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
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	const int n = 3;
	vector<pt> p;
	for(int i=0; i<n; i++) {
		ld x, y;
		cin >> x >> y;
		p.push_back(pt(x, y));
	}

	pt g = accumulate(p.begin(), p.end(), pt(0,0)) / (ld)3;
	cout << g.real() << " " << g.imag() << nl;
	for(int i=1; i<n; i++) {
		pt o = (p[i] - p[0]) / (ld)9 + g;
		cout << o.real() << " " << o.imag() << nl;
		assert(abs(o-g) > 1+EPS);
	}
	for(int i=0; i<n; i++) {
		pt o = (ld)2*g - p[i];
		cout << o.real() << " " << o.imag() << nl;
	}

	return 0;
}
