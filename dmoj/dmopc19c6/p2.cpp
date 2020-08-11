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

	int a, b;
	cin >> a >> b;

	vector<pair<int,int>> pc;
	for(int i=2; i<=a; i++) {
		if(a%i == 0) {
			int cnt = 0;
			while(a%i == 0) {
				a /= i;
				cnt++;
			}
			pc.push_back(make_pair(i, cnt));
		}
	}

	int ans = INF;
	for(auto [p, cnt] : pc) {
		int have = 0;
		for(int i=p; i<=b; i*=p) {
			have += b/i;
		}
		ans = min(ans, have/cnt);
	}
	cout << ans << nl;

	return 0;
}
