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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
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

	int m, n;
	cin >> m >> n;
	string s;
	cin >> s;
	unordered_set<int> vals;
	vals.insert(s.size());
	vector<pii> ord;
	for (int i=0;i<n;i++) {
		int a,b;
		cin >> a >> b;
		ord.push_back(pii(b, a));
		vals.insert(a);
	}
	sort(ord.begin(), ord.end());

	string ans;
	for(const pii& it:ord) {
		int i = it.second;
		do {
			ans.push_back(s[i]);
		} while (!vals.count(++i));
	}
	cout << ans << nl;

	return 0;
}
