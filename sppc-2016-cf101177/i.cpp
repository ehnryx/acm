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

	ll total = 0;
	int a, b;

	map<int,int> lis;
	for (int i=0; i<n; i++) {
		cin >> a >> b;
		int len = b-a+1;
		total += len;

		auto it = lis.lower_bound(a);
		while (it != lis.end()) {
			if (it->second <= len) {
				len -= it->second;
				it = lis.erase(it);
			}
			else {
				it->second -= len;
				break;
			}
		}
		lis[a] = b-a+1;
	}

	ll ans = 0;
	for (const pii& it : lis) {
		ans += it.second;
	}
	cout << ans << nl;

	return 0;
}
