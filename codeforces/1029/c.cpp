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

	int n;
	cin >> n;

	int a, b;
	vector<pii> p;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		p.push_back(pii(a, 1));
		p.push_back(pii(b, -1));
	}
	sort(p.begin(), p.end());

	int ans = 0;
	int cur = 0;
	int len = 0;
	int pre = 0;
	for (const pii& it : p) {
		if (cur >= n-1) {
			len += it.first - pre;
		} else {
			ans = max(ans, len);
			len = 0;
		}
		cur += it.second;
		pre = it.first;
	}

	cout << ans << nl;

	return 0;
}
