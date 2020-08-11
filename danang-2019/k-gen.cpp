#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define nl '\n'

const int INF = 0x3f3f3f3f;

enum {
	LEFT,
	RIGHT,
};

const int N = 100 + 1;
int dp[N][N][2], dir[N][N][2], tor[N][N][2];
vector<pair<int,int>> moves[N][N][2];
int g[N];

int solve(int l, int r, bool rev) {
	if(l > r) return 0;
	if(dp[l][r][rev] != -1) return dp[l][r][rev];
	vector<int> h;
	for(int i=l; i<=r; i++) {
		h.push_back(g[i]);
	}
	if(rev) {
		sort(h.begin(), h.end(), greater<int>());
	} else {
		sort(h.begin(), h.end());
	}

	int best = INF;
	if(h.front() == g[l] && solve(l+1, r, rev) < best) {
		best = solve(l+1, r, rev);
		moves[l][r][rev].clear();
		dir[l][r][rev] = LEFT;
	}
	if(h.back() == g[r] && solve(l, r-1, rev) < best) {
		best = solve(l, r-1, rev);
		moves[l][r][rev].clear();
		dir[l][r][rev] = RIGHT;
	}
	if(h.front() == g[r] && solve(l, r-1, rev^1) + 1 < best) {
		best = solve(l, r-1, rev^1) + 1;
		moves[l][r][rev].clear();
		moves[l][r][rev].push_back(make_pair(l, r));
		dir[l][r][rev] = RIGHT;
		tor[l][r][rev] = 1;
	}
	if(h.back() == g[l] && solve(l+1, r, rev^1) + 1 < best) {
		best = solve(l+1, r, rev^1) + 1;
		moves[l][r][rev].clear();
		moves[l][r][rev].push_back(make_pair(l, r));
		dir[l][r][rev] = LEFT;
		tor[l][r][rev] = 1;
	}
	for(int i=0; i<h.size(); i++) {
		if(h[i] == g[l] && solve(l+1, r, rev) + 2 < best) {
			best = solve(l+1, r, rev) + 2;
			moves[l][r][rev].clear();
			moves[l][r][rev].push_back(make_pair(l, l+i));
			moves[l][r][rev].push_back(make_pair(l+1, l+i));
			dir[l][r][rev] = LEFT;
		}
		if(h[i] == g[r] && solve(l, r-1, rev) + 2 < best) {
			best = solve(l, r-1, rev) + 2;
			moves[l][r][rev].clear();
			moves[l][r][rev].push_back(make_pair(l+i, r));
			moves[l][r][rev].push_back(make_pair(l+i, r-1));
			dir[l][r][rev] = RIGHT;
		}
	}

	return dp[l][r][rev] = best;
}

vector<pair<int,int>> ans;
void recover(int l, int r, bool rev) {
	if(l > r) return;
	for(const auto& it : moves[l][r][rev]) {
		ans.push_back(it);
	}
	if(dir[l][r][rev] == LEFT) {
		recover(l+1, r, rev ^ tor[l][r][rev]);
	} else {
		recover(l, r-1, rev ^ tor[l][r][rev]);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n;
	cin >> n;
	for(int i=1; i<=n; i++) {
		g[i] = i;
	}
	mt19937 rng(time(0));
	shuffle(g+1, g+n+1, rng);
	memset(dp, -1, sizeof dp);
	assert(solve(1, n, false) <= 191);
	recover(1, n, false);

	reverse(ans.begin(), ans.end());
	cout << ans.size() << nl;
	for(const auto& it : ans) {
		cout << it.first << " " << it.second << nl;
	}
	cerr<<ans.size()<<" MOVES "<<nl;

	return 0;
}
