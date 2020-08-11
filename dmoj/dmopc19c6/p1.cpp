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
pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a);
}

pair<ll,ll> slope(const pt& a, const pt& b) {
	ll dx = a.real() - b.real();
	ll dy = a.imag() - b.imag();
	ll g = __gcd(dx, dy);
	return make_pair(dx / abs(g), dy / abs(g));
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int a, b, x, y;
	cin >> a >> b >> x >> y;
	int A, B, X, Y;
	cin >> A >> B >> X >> Y;

	pt sa(a,b), sb(x,y);
	pt SA(A,B), SB(X,Y);
	if(abs(cp(sa-sb, sa-SA)) < EPS && abs(cp(sa-sb, sa-SB)) < EPS) {
		cout << "coincident" << nl;
	} else if(slope(sa, sb) == slope(SA, SB)) {
		cout << "parallel" << nl;
	} else {
		pt it = line_inter(sa, sb, SA, SB);
		cout << it.real() << " " << it.imag() << nl;
	}

	return 0;
}
