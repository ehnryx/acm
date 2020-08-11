//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "rhymes"

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
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif

	int n;
	cin >> n;
	vector<vector<int>> ans;
	unordered_map<int,vector<int>> cnt;
	int two = 0;
	for(int i=1; i<=n; i++) {
		int a;
		cin >> a;
		cnt[a].push_back(i);
		if(cnt[a].size() == 4) {
			ans.push_back(cnt[a]);
			cnt.clear();
			two = 0;
		} else if(cnt[a].size() == 2) {
			if(!two) {
				two = a;
			} else {
				vector<int> line = {cnt[a][0], cnt[a][1], cnt[two][0], cnt[two][1]};
				sort(line.begin(), line.end());
				ans.push_back(line);
				cnt.clear();
				two = 0;
			}
		}
	}

	cout << ans.size() << nl;
	for(const auto& v : ans) {
		for(int it : v) {
			cout << it << " ";
		}
		cout << nl;
	}

	return 0;
}
