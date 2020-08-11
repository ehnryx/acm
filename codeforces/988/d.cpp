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



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;

	unordered_set<ll> p;
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		p.insert(a);
	}

	pii ans = pii(INF,INF);
	for (int i=1; i<31; i++) {
		for (ll it : p) {
			if (p.count(it+(1LL<<i))) {
				if (p.count(it+(2LL<<i))) {
					cout << 3 << nl;
					cout << it << " " << it+(1LL<<i) << " " << it+(2LL<<i) << nl;
					return 0;
				} else {
					ans = pii(it, it+(1LL<<i));
				}
			}
		}
	}

	if (ans.first != INF) {
		cout << 2 << nl;
		cout << ans.first << " " << ans.second << nl;
	} else {
		cout << 1 << nl;
		cout << *p.begin() << nl;
	}

	return 0;
}
