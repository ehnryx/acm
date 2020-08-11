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

typedef long double ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

pair<ll,ll> get_coeffs(ll a, ll b, ll c, ll d) {
	ll bot = a*c - b*b;
	if(abs(bot) > EPS && abs(c) > EPS) {
		ll A = (c*c - d*b) / bot;
		ll B = (d - A*b) / c;
		return make_pair(A, B);
	}

	bot = c*b - a*d;
	if(abs(bot) > EPS && abs(b) > EPS) {
		ll B = (b*b - a*c) / bot;
		ll A = (d - B*c) / b;
		return make_pair(A, B);
	}

	if(abs(c) > EPS) {
		ll A = 0;
		ll B = d/c;
		return make_pair(A, B);
	}

	return make_pair(0, 0);
}

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(string line; getline(cin, line); ) {
		istringstream in(line);
		ll d, p;
		in >> d >> p;
		vector<ll> s;
		for(int v; in >> v; ) {
			s.push_back(v);
		}

		if(s.size() < d+1) {
			int z = s.size();
			auto [a, b] = get_coeffs(s[z-4], s[z-3], s[z-2], s[z-1]);
			for(int i=s.size(); i<d+1; i++) {
				if(s[i-1] > p) {
					s.push_back(INFLL);
				} else {
					s.push_back(min(INFLL, a*s[i-2] + b*s[i-1]));
				}
			}
		}

		if(p < s.front()) {
			cout << "The spider is going to fall!" << nl;
		} else if(p > s.back()) {
			cout << "The spider may fall!" << nl;
		} else {
			cout << s.end() - upper_bound(s.begin(), s.end(), p) << nl;
		}
	}

	return 0;
}
