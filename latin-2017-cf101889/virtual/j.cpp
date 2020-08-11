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
const int N = 1e5+10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int can[N];
bool vis[N];
string s; int n;

bool dfs(int sz) {
	if (can[sz] != -1) return can[sz];
	memset(vis, 0, sizeof vis);
	for (int i = 0; i < sz; i++) {
		bool shit = 0;
		for (int j = i; !vis[j]; j = (j + sz)%n) {
			if (s[j] == 'P') {
				shit = 1;
				break;
			}
			vis[j] = 1;
		}
		if (!shit) {
			return (can[sz] = 1);
		}
	}
	return (can[sz] = 0);
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	memset(can, -1, sizeof can);
	cin >> s;
	n = s.size();
	int ans = 0;
	for (int i = 1; i < n; i++) {
		ans += dfs(__gcd(i, n));
	}
	cout << ans << endl;

	return 0;
}
