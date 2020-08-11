#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

set<vector<int>> vis;

int length;
bool solve(int n, const multiset<int>& dist, vector<int>& cur) {
	if (n == 0) return true;
	if (n < 0) return false;

	vector<int> ordered = cur;
	sort(ordered.begin(), ordered.end());
	if (vis.count(ordered)) return false;

	int d = *dist.rbegin();
	for (int left = 0; left <= 1; left++) {
		int right = !left;
		bool good = true;
		multiset<int> nxt = dist;

		for (int p : cur) {
			if (nxt.count(abs(d-p)) < left || nxt.count(abs(length-d-p)) < right) {
				good = false;
				break;
			}
			if (left) nxt.erase(nxt.find(abs(d-p)));
			else nxt.erase(nxt.find(abs(length-d-p)));
		}

		if (good) {
			if (left) cur.push_back(d);
			else cur.push_back(length-d);
			if (solve(n-1, nxt, cur)) return true;
			cur.pop_back();
		}
	}

	vis.insert(ordered);
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		int m = n*(n-1)/2;

		int a;
		multiset<int> dist;
		for (int i = 0; i < m; i++) {
			cin >> a;
			dist.insert(a);
		}

		length = *dist.rbegin();
		vector<int> cur = {0,length};
		dist.erase(prev(dist.end()));

		vis.clear();
		solve(n-2, dist, cur);

		sort(cur.begin(), cur.end());
		for (int it : cur) {
			cout << it << " ";
		}
		cout << nl;
	}

	return 0;
}
