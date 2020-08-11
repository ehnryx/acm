#include <bits/stdc++.h>
using namespace std;

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
const int N = 1e5+10;

int n;
int a[N];
int num[N], ans[N];

vector<int> bounds;

void pre() {
	bool inc = (a[0] <= a[1]);
	for (int i = 1; i < n-1; i++) {
		if ((inc && a[i] > a[i+1]) || (!inc && a[i] <= a[i+1])) {
			bounds.push_back(i);
		}
		inc = (a[i] <= a[i+1]);
	}
	bounds.push_back(n-1);
	//for (int i : bounds) cerr << i << " "; cerr << nl;
	for (int i = 2; i <= n; i++) {
		int cur = 0;
		auto it = lower_bound(bounds.begin(), bounds.end(), cur);
		while (cur < n) {
			if (*it == cur) ++it;
			num[i]++;
			if (it == bounds.end()) break;
			int sz = *it - cur + 1;
			//cerr << i << " " << cur << " " << sz << nl;
			ans[i] += max(0, min(i, n - cur) - sz);
			cur += max(i, sz);
			it = lower_bound(it, bounds.end(), cur);
		}
	}
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	pre();
	int q; cin >> q;
	while (q--) {
		int k; cin >> k;
		cout << num[k] << " " << ans[k] << nl;
	}
	return 0;
}
