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

int N;

struct SegTree {
	vector<bool> lazy[2];
	vector<ll> segt, max_val[2], min_val[2];

	SegTree(int n) {
		N = 1 << (32 - __builtin_clz(n));
		segt.resize(2*N, 0);
		for (int i = 0; i < 2; i++) {
			max_val[i].resize(2*N, 0);
			min_val[i].resize(2*N, 0);
			lazy[i].resize(2*N);
		}
	}

	void push_down(int i, int idx) {
		if (lazy[idx][i]) {
			// update left child
			segt[i<<1] += (max_val[idx][i] > max_val[idx][i<<1]) ? max_val[idx][i] - max_val[idx][i<<1] : 0;
			max_val[idx][i<<1] = max(max_val[idx][i<<1], max_val[idx][i]);
			min_val[idx][i<<1] = min(min_val[idx][i<<1], min_val[idx][i]);
			// update right child
			segt[i<<1|1] += (max_val[idx][i] > max_val[idx][i<<1|1]) ? max_val[idx][i] - max_val[idx][i<<1|1] : 0;
			max_val[idx][i<<1|1] = max(max_val[idx][i<<1|1], max_val[idx][i]);
			min_val[idx][i<<1|1] = min(min_val[idx][i<<1|1], min_val[idx][i]);
			// update lazy
			lazy[idx][i<<1] = lazy[idx][i<<1|1] = true;
			lazy[idx][i] = false;
		}
	}

	void update(int left, int right, ll val, int idx, int i=1, int l=0, int r=N-1) {
		if (right < l || left > r || min_val[idx][i] >= val) {
			return;
		}
		if (left <= l && r <= right && min_val[idx][i] == max_val[idx][i]) {
			segt[i] += (val > max_val[idx][i]) ? val - max_val[idx][i] : 0;
			min_val[idx][i] = val;
			max_val[idx][i] = max(max_val[idx][i], val);
			lazy[idx][i] = true;
			//cerr << "put @ " << i << ',' << idx << ": " << l << " -- " << r << " val: " << segt[i] << endl;
			return;
		}
		push_down(i, idx);

		int mid = (l + r) / 2;
		update(left, right, val, idx, i<<1, l, mid);
		update(left, right, val, idx, i<<1|1, mid+1, r);

		max_val[idx][i] = max(max_val[idx][i<<1], max_val[idx][i<<1|1]);
		min_val[idx][i] = min(min_val[idx][i<<1], min_val[idx][i<<1|1]);
		segt[i] = min(segt[i<<1], segt[i<<1|1]);
	}

	ll query(int x, int i=1, int l=0, int r=N-1) {
		if (r == x) {
			return segt[i];
		}
		push_down(i, 0);
		push_down(i, 1);

		int mid = (l + r) / 2;
		if (x <= mid) return query(x, i<<1, l, mid);
		else return min(query(mid, i<<1, l, mid), query(x, i<<1|1, mid+1, r));
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	while (cin >> n) {
		SegTree segtree(n);
		vector<ll> start(n+1);
		vector<ll> value(n+1);
		vector<ll> dp(n+1);

		start[0] = 0;
		for (int i = 1; i <= n; i++) {
			cin >> start[i] >> value[i];
		}
		//cerr << "INPUT OK " << endl;

		dp[0] = 0;
		for (int i = 1; i <= n; i++) {
			segtree.update(i-1, i-1, dp[i-1], 0);
			segtree.update(0, i-1, start[i], 0);
			segtree.update(0, i-1, 2*value[i], 1);
			dp[i] = segtree.query(i-1); // inclusive
			//cerr << "DP[" << i << "]" << " = " << dp[i] << endl;
		}
		cout << dp[n] << nl;
		//cerr << endl;
	}

	return 0;
}
