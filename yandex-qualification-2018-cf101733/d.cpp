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



//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, q;
	cin >> n >> q;

	ll a[n+1];
	for (int i=1; i<=n; i++) {
		cin >> a[i];
	}

	while (q--) {
		int l, r;
		cin >> l >> r;
		r = min(r, l+86);

		vector<pair<ll,int>> v;
		for (int i=l; i<=r; i++) {
			v.push_back(pair<ll,int>(a[i],i));
		}
		sort(v.begin(), v.end());

		bool ok = false;
		for (int i=2; i<v.size(); i++) {
			if (v[i-2].first + v[i-1].first > v[i].first) {
				ok = true;
				cout << v[i-2].second << " " << v[i-1].second << " " << v[i].second << nl;
				break;
			}
		}
		if (!ok) {
			cout << -1 << nl;
		}
	}

	return 0;
}
