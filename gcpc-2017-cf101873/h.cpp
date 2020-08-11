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

const int N = 80+1;
vector<int> adj[N];
int dp[N][N];

int build(int root, int cur, int par = 0) {
	if (dp[root][cur] != -1) return dp[root][cur];
	int maxv = 0;
	for (int x : adj[cur]) {
		if (x != par) {
			maxv = max(maxv, 1 + build(root, x, cur));
		}
	}
	return dp[root][cur] = maxv;
}

bool walk(int par, int cur, int s) {
	if (cur == s) return true;
	for (int x : adj[cur]) {
		if (x != par && walk(cur, x, s)) {
			return true;
		}
	}
	return false;
}

void init() {
	memset(dp, -1, sizeof dp);
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
	init();

	int n, r, h, m, a, b;
	cin >> n;
	cin >> r;
	cin >> h;
	cin >> m;

	for (int i = 1; i < n; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	int ans = INF;
	for (int i = 1; i <= n; i++) {
		ans = min(ans, 1 + build(i, i));
		if (i == h || i == m) {
			for (int j : adj[i]) {
				if (walk(i, j, r)) {
					ans = min(ans, 1 + build(i, j));
				}
			}
		}
	}
	cout << ans << nl;

	return 0;
}
