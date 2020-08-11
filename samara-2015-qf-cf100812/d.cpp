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

	unordered_map<ll,int> memo;
	pii ans(-1,INF);
	ll sum = 0;
	int a;
	for (int i = 1; i <= n; i++) {
		memo[sum] = i;
		cin >> a;
		sum += a;
		if (memo.count(sum) && i - memo[sum] < ans.second) {
			ans = pii(memo[sum], i - memo[sum]);
		}
	}

	if (ans.first == -1) {
		cout << -1 << nl;
	} else {
		cout << ans.first << " " << ans.second+1 << nl;
	}

	return 0;
}
