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

	int n, k;
	cin >> n >> k;
	k = (2*n-1)/3;

	int bf = -1;
	for (int i=1; i<=n; i++) {
		if (i + (n-i+1)/2 >= k) {
			bf = i;
			break;
		}
	}

	vector<int> ans;
	for (int i=1; i<1<<bf; i++) {
		ans.push_back(32-__builtin_clz(i&-i));
	}
	for (int j=bf; j<=n; j++) {
		ans.push_back(j);
	}
	for (int i=1; i<1<<bf; i++) {
		ans.push_back(32-__builtin_clz(i&-i));
	}

	cout << ans.size() << nl;
	for (int it : ans) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}
