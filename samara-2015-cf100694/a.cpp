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

const int N = 1e4+1;
const int M = 500+200+200+7;
const int offset = 205;
int dp[N][M][3]; // id, space, activated
int price[N], weight[N], active[N];

void init() {
	memset(dp, -1, sizeof dp);
}

int n, m;
int solve(int id, int space, int ammo) {
	if (dp[id][space][ammo] != -1) return dp[id][space][ammo];
	if (id == 0) return space >= offset ? 0 : -INF;

	int res = solve(id-1, space, ammo);
	if (weight[id] <= space) {
		res = max(res, price[id] + solve(id-1, space-weight[id], ammo));
	}
	if (ammo > 0 && weight[id] <= space + active[id]) {
		res = max(res, price[id] + solve(id-1, space-weight[id]+active[id], ammo-1));
	}

	return dp[id][space][ammo] = res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	cin >> n >> m;
	for (int i=1; i<=n; i++) {
		cin >> price[i] >> weight[i] >> active[i];
	}

	cout << solve(n, m+offset, 2) << nl;

	return 0;
}
