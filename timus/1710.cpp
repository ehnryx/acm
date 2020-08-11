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

ld cp(const pt& a, const pt& b) {
	return imag(conj(a) * b);
}
pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
	return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

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

	if(abs(p[2]-p[1]) > abs(p[1]-p[0]) - EPS) {
		cout << "YES" << nl;
	} else {
		pt dir = (p[2] - p[0]) * pt(0, 1);
		pt mid = line_inter(p[1], p[1] + dir, p[0], p[2]);
		if(abs(p[2] - mid) < EPS) {
			cout << "YES" << nl;
		} else {
			cout << "NO" << nl;
			p[2] = (ld)2*mid - p[2];
			for(int i=0; i<n; i++) {
				cout << p[i].real() << " " << p[i].imag() << nl;
			}
		}
	}

	return 0;
}
