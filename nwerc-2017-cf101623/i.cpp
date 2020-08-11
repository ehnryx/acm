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

struct App {
	int d, s, id, v;
	App(){}
	App(int down, int store, int i):
		d(max(down,store)), s(store), id(i), v(s-d) {}
	bool operator < (const App& o) const {
		return v < o.v;
	}
};

const int N = 5e2+1;
const int C = 1e4+1;
int dp[N][C], val[N][C];
pii pre[N][C];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, c, d, s;
	cin >> n >> c;

	vector<App> app;
	for (int i=1; i<=n; i++) {
		cin >> d >> s;
		app.push_back(App(d,s,i));
	}
	sort(app.begin(), app.end());

	memset(dp, -1, sizeof dp);
	dp[0][0] = 0;
	for (int i=0; i<n; i++) {
		auto& a = app[i];
		for (int j=0; j<=c; j++) {
			if (dp[i][j] != -1) {
				if (j+a.d<=c && dp[i][j]+1 > dp[i+1][j+a.s]) {
					dp[i+1][j+a.s] = dp[i][j]+1;
					pre[i+1][j+a.s] = pii(i,j);
					val[i+1][j+a.s] = a.id;
				}
				if (dp[i][j] > dp[i+1][j]) {
					dp[i+1][j] = dp[i][j];
					pre[i+1][j] = pre[i][j];
					val[i+1][j] = val[i][j];
				}
			}
		}
	}

	int best = 0;
	for (int j=1; j<=c; j++) {
		if (dp[n][j] > dp[n][best]) {
			best = j;
		}
	}

	vector<int> ans;
	for (pii cur = pii(n,best); val[cur.first][cur.second]; cur = pre[cur.first][cur.second]) {
		ans.push_back(val[cur.first][cur.second]);
	}
	reverse(ans.begin(), ans.end());
	cout << ans.size() << nl;
	for (int it : ans) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}
