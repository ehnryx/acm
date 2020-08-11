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

	int T, W;
	cin >> T >> W;
	while(T--) {
		vector<ll> r(7);
		ll tot, cur;

		cur = 200;
		cout << cur << endl;
		cin >> tot; if(tot == -1) break;
		r[4] = tot>>(200/4) & 127;
		r[5] = tot>>(200/5) & 127;
		r[6] = tot>>(200/6) & 127;

		cur = 50;
		cout << cur << endl;
		cin >> tot; if(tot == -1) break;
		tot -= (r[4]<<(50/4)) + (r[5]<<(50/5)) + (r[6]<<(50/6));
		r[1] = tot>>(50/1) & 127;
		r[2] = tot>>(50/2) & 127;
		r[3] = tot>>(50/3) & 127;

		for(int i=1; i<=6; i++) {
			cout << r[i] << " ";
		}
		cout << endl;
		cin >> tot; if(tot == -1) break;
	}

	return 0;
}
