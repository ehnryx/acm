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



int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	string s;
	cin >> s;
	int n = s.size();
	string t = "0" + s + "0";
	set<int> zero;
	vector<int> two;
	for(int i=0; i<=n+1; i++) {
		if(t[i] == '0') {
			zero.insert(i);
		} else if(t[i] == '2') {
			two.push_back(i);
		}
	}

	for(int i : two) {
		if(t[i] != '2') continue;
		auto it = zero.upper_bound(i);
		int l = *prev(it);
		int r = *it;
		int j = r + l - i;
		--t[i];
		if(--t[j] == '0') {
			zero.insert(j);
		}
		if(l > 0) {
			t[l] = '1';
			zero.erase(l);
		}
		if(r <= n) {
			t[r] = '1';
			zero.erase(r);
		}
	}

	for(int i=1; i<=n; i++) {
		cout << t[i];
	}
	cout << nl;

	return 0;
}

