#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef mt19937 RNG;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

#define DP 0
#define MQ 1

int N;
struct SegTree {
	vector<bool> lazy[2];
	vector<ll> segt, maxv[2], minv[2];
	SegTree(int n) {
		N = 1 << (32 - __builtin_clz(n));
		segt.resize(2*N, 0);
		for (int i = 0; i < 2; i++) {
			maxv[i].resize(2*N, 0);
			minv[i].resize(2*N, 0);
			lazy[i].resize(2*N);
		}
	}

	void push(int id, int i) {
		if (lazy[id][i]) {
			segt[i<<1] += maxv[id][i] - maxv[id][i<<1];
			segt[i<<1|1] += maxv[id][i] - maxv[id][i<<1|1];
			maxv[id][i<<1] = maxv[id][i<<1|1] = minv[id][i<<1] = minv[id][i<<1|1] = maxv[id][i];
			lazy[id][i<<1] = lazy[id][i<<1|1] = true;
			lazy[id][i] = false;
		}
	}

	void update(int id, int left, int right, ll val, int i=1, int l=0, int r=N-1) {
		if (right < l || r < left || val <= minv[id][i]) {
			return; 
		}
		if (left <= l && r <= right && minv[id][i] == maxv[id][i]) {
			segt[i] += val - maxv[id][i];
			maxv[id][i] = minv[id][i] = val;
			lazy[id][i] = true;
			return;
		}
		push(0, i);
		push(1, i);

		int mid = (l + r) / 2;
		update(id, left, right, val, i<<1, l, mid);
		update(id, left, right, val, i<<1|1, mid+1, r);
		segt[i] = min(segt[i<<1], segt[i<<1|1]);
		maxv[id][i] = max(maxv[id][i<<1], maxv[id][i<<1|1]);
		minv[id][i] = min(minv[id][i<<1], minv[id][i<<1|1]);
	}

	ll query(int left, int right, int i=1, int l=0, int r=N-1) {
		if (right < l || r < left) {
			return INFLL;
		}
		if (left <= l && r <= right) {
			return segt[i];
		}
		push(0, i);
		push(1, i);

		int mid = (l + r) / 2;
		return min(query(left, right, i<<1, l, mid), query(left, right, i<<1|1, mid+1, r));
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	while (cin >> n) {
		SegTree memo(n);
		ll start[n], value[n];
		for (int i = 0; i < n; i++) {
			cin >> start[i] >> value[i];
		}

		ll dp[n+1];
		dp[0] = 0;
		for (int i = 0; i < n; i++) {
			memo.update(DP, i, i, dp[i]);
			memo.update(DP, 0, i, start[i]);
			memo.update(MQ, 0, i, 2*value[i]);
			dp[i+1] = memo.query(0, i);
		}
		cout << dp[n] << nl;
	}

	return 0;
}
