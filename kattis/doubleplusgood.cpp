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
	cout << fixed << setprecision(10);

	string s;
	cin >> s;
	vector<int> p;
	for(int i=0; i<s.size(); i++) {
		if(s[i] == '+') {
			p.push_back(i);
		}
	}

	int n = p.size();
	set<ll> all;
	for(int bm=0; bm<1<<n; bm++) {
		for(int i=0; i<n; i++) {
			if(bm & 1<<i) {
				s[p[i]] = '.';
			}
		}
		ll cur = 0;
		ll res = 0;
		for(int i=0; i<s.size(); i++) {
			if(s[i] == '+') {
				res += cur;
				cur = 0;
			} else if(s[i] != '.') {
				cur = cur*10 + s[i]-'0';
			}
		}
		res += cur;
		all.insert(res);
		for(int i=0; i<n; i++) {
			if(bm & 1<<i) {
				s[p[i]] = '+';
			}
		}
	}

	cout << all.size() << nl;

	return 0;
}
