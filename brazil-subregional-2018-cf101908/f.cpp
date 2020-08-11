#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int N = 10;

struct show {
	int l, r, x;
	bool operator < (const show& o) const {
		return tie(l, r) < tie(o.l, o.r);
	}
};

int n;
vector<show> shows[N];

int dp[N][1 << N][1010];
int solve(int cur, int mask, int ind) {
	if (ind >= shows[cur].size()) return mask ? -INF : 0;
	mask &= (((1 << n) - 1) ^ (1 << cur));
	if (dp[cur][mask][ind] != -1) return dp[cur][mask][ind];
	int best = solve(cur, mask, ind+1);
	for (int i = 0; i < n; i++) {
		int ni = upper_bound(shows[i].begin(),
												 shows[i].end(),
												 show{shows[cur][ind].r, -INF, 0})
			- shows[i].begin();
		best = max(best, solve(i, mask, ni) + shows[cur][ind].x);
	}
	//cerr << "VISIT " << cur << " " << bitset<4>(mask) << " " << ind << " = " << best << nl;
	return dp[cur][mask][ind] = best;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		int m; cin >> m;
		for (int j = 0; j < m; j++) {
			show s; cin >> s.l >> s.r >> s.x;
			shows[i].push_back(s);
		}
		sort(shows[i].begin(), shows[i].end());
	}
	memset(dp, -1, sizeof dp);
	int ans = -1;
	for (int i = 0; i < n; i++) {
		ans = max(ans, solve(i, (1 << n) - 1, 0));
	}
	cout << ans << nl;

	return 0;
}
