#include <bits/stdc++.h>
using namespace std;
#define problem_name "hard"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 62;

struct sq {
	int x, y, l;
	sq add(int a, int b) const {
		return sq{x+a, y+b, l};
	}
};

int dp[N][N];
vector<sq> ans[N][N];

void upd(int xoff, int yoff, int nx, int ny, vector<sq>& v) {
	for (const sq& s : ans[nx][ny]) {
		v.push_back(s.add(xoff, yoff));
	}
}

int solve(int x, int y) {
	if (dp[x][y] != -1) return dp[x][y];
	if (x == y) {
		ans[x][y] = {sq{0, 0, x}};
		return dp[x][y] = 1;
	}
	// horiz
	int best = INF;
	int bx, by, cx, cy, xoff, yoff;
	for (int i = 1; i < x; i++) {
		int cur = solve(i, y) + solve(x - i, y);
		if (best > cur) {
			best = cur;
			tie(bx, by, cx, cy) = make_tuple(i, y, x-i, y);
			xoff = i;
			yoff = 0;
		}
	}
	for (int i = 1; i < y; i++) {
		int cur = solve(x, i) + solve(x, y - i);
		if (best > cur) {
			best = cur;
			tie(bx, by, cx, cy) = make_tuple(x, i, x, y-i);
			xoff = 0;
			yoff = i;
		}
	}
	ans[x][y] = ans[bx][by];
	upd(xoff, yoff, cx, cy, ans[x][y]);
	return dp[x][y] = best;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifdef ONLINE_JUDGE
	freopen(problem_name ".in", "r", stdin);
	freopen(problem_name ".out", "w", stdout);
#endif

	memset(dp, -1, sizeof dp);
	int T; cin >> T;
	while (T--) {
		int w, h; cin >> w >> h;
		cout << solve(w, h) << nl;
		for (const sq& s : ans[w][h]) {
			cout << s.x << " " << s.y << " " << s.l << nl;
		}
	}

	return 0;
}
