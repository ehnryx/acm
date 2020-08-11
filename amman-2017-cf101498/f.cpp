#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e5+1;
int arr[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n, k;
		cin >> n >> k;

		map<int,vector<int>> index;
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
			index[arr[i]].push_back(i);
		}
		for (pair<const int,vector<int>>& it : index) {
			it.second.push_back(n);
		}

		int ans = 0;
		set<int> cur;
		for (int i = 0; i < n; i++) {
			if (cur.count(i)) cur.erase(i);
			else ans++;

			if (cur.size() == k) cur.erase(prev(cur.end()));
			cur.insert(*upper_bound(index[arr[i]].begin(), index[arr[i]].end(), i));
		}
		cout << ans << nl;
	}

	return 0;
}
