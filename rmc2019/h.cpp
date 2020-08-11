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

ld cp(const pt& a, const pt& b) {
	return imag(conj(a)*b);
}

pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
	return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

bool parallel(pt a, pt b) {
	return abs(cp(a, b)) < EPS;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	vector<pair<pt,pt>> lines;
	for(int i=0; i<n; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		pt u(a,b), v(c,d);
		lines.push_back(make_pair(u, v));
	}

	ld ans = 0;
	for(auto [a, b] : lines) {
		for(auto [c, d] : lines) {
			for(auto [e, f] : lines) {
				if(parallel(a-b, c-d) || parallel(c-d, e-f) || parallel(e-f, a-b)) {
					continue;
				}
				pt ac = line_inter(a, b, c, d);
				pt ce = line_inter(c, d, e, f);
				pt ea = line_inter(e, f, a, b);
				ans = max(ans, abs(ac-ce) + abs(ce-ea) + abs(ea-ac));
			}
		}
	}
	if(ans < EPS) {
		cout << "no triangle" << nl;
	} else {
		cout << ans << nl;
	}

	return 0;
}
