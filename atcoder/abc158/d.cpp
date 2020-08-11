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

	string s;
	cin >> s;
	deque<char> res;
	for(char c : s) {
		res.push_back(c);
	}

	int m;
	cin >> m;
	bool rev = false;
	for(int i=0; i<m; i++) {
		int t;
		cin >> t;
		if(t == 1) {
			rev ^= 1;
		} else {
			int f; char c;
			cin >> f >> c;
			f = (f-1) ^ rev;
			if(f == 0) {
				res.push_front(c);
			} else {
				res.push_back(c);
			}
		}
	}

	if(rev) {
		while(!res.empty()) {
			cout << res.back();
			res.pop_back();
		}
	} else {
		while(!res.empty()) {
			cout << res.front();
			res.pop_front();
		}
	}
	cout << nl;

	return 0;
}
