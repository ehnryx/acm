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
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) {
	return imag(conj(a) * b);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(2);

	int n;
	cin >> n;
	int d, l;
	cin >> d >> l;
	vector<pt> p;
	for(int i=0; i<n; i++) {
		int x, y;
		cin >> x >> y;
		p.push_back(pt(x, y));
	}

	ld left = 0;
	ld right = 2e3;
	while(right - left > EPS) {
		ld mid = (left + right) / 2;
		ld area = 0;
		pt rem = pt(0, -2);
		for(int i=0; i<n; i++) {
			int j = (i+1) % n;
			if(p[i].imag() < mid && p[j].imag() < mid) {
				area += cp(p[i], p[j]);
			} else if(p[i].imag() < mid && p[j].imag() >= mid) {
				ld f = (mid - p[i].imag()) / (p[j].imag() - p[i].imag());
				pt v = p[i] + f * (p[j] - p[i]);
				area += cp(p[i], v);
				if(rem.imag() > -1) {
					area += cp(v, rem);
				}
				rem = v;
			} else if(p[i].imag() >= mid && p[j].imag() < mid) {
				ld f = (mid - p[i].imag()) / (p[j].imag() - p[i].imag());
				pt v = p[i] + f * (p[j] - p[i]);
				area += cp(v, p[j]);
				if(rem.imag() > -1) {
					area += cp(rem, v);
				}
				rem = v;
			}
		}
		if(area/2 * d < l * 1000) {
			left = mid;
		} else {
			right = mid;
		}
	}
	cout << right << nl;

	return 0;
}
