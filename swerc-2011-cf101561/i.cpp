//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
const ll MOD = 998244353;
const ld EPS = 1e-7;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

#undef M_PIl
const ld M_PIl = acos((ld)-1);

pt circumcenter(pt a, pt b, pt c) {
	ld A = norm(b-c);
	ld B = norm(c-a);
	ld C = norm(a-b);
	ld fa = A*(B+C-A);
	ld fb = B*(C+A-B);
	ld fc = C*(A+B-C);
	return (fa*a + fb*b + fc*c) / (fa+fb+fc);
}

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(ld x[3], y[3]; cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2]; ) {
		pt v[3];
		for(int i=0; i<3; i++) {
			v[i] = pt(x[i], y[i]);
		}
		pt c = circumcenter(v[0], v[1], v[2]);
		ld a = arg((v[1]-c) / (v[0]-c));
		ld b = arg((v[2]-c) / (v[0]-c));
		int ans = -1;
		for(int i=3; i<=1000; i++) {
			ld g = 2*M_PIl / i;
			if(abs(a/g - round(a/g)) < EPS && abs(b/g - round(b/g)) < EPS) {
				ans = i;
				break;
			}
		}
		assert(ans != -1);
		cout << ans << nl;
	}


	return 0;
}
