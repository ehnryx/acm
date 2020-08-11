#include <bits/stdc++.h>

using namespace std;

const int L = 20 + 5;
const int N = 200000 + 5;

const long long INF = 0x3f3f3f3f3f3f3f3fLL;
pair<long long, int> rmq[L][2*N];

void build_rmq(int n) {
	for (int i = 1; (1 << i - 1) <= n; i++) {
		for (int j = 1; j <= n; j++) {
			rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + (1 << i - 1)]);
		}
	}
}

inline pair<long long, int> query_rmq(int l, int r) {
	int j = 31 - __builtin_clz(r-l+1);
	return min(rmq[j][l], rmq[j][r-(1<<j)+1]);
}

long long query(long long v, int l, int r) {
	while (l <= r) {
		int ll = l, rr = r;
		pair<long long, int> ans = make_pair(-1, -1);
		while (ll <= rr) {
			int mid = (ll + rr) / 2;
			auto pr = query_rmq(l, mid);
			if (pr.first <= v) {
				ans = pr;
				rr = mid - 1;
			} else {
				ll = mid + 1;
			}
		}
		if (ans.first == -1) {
			return v;
		} else {
			v %= ans.first;
			l = ans.second + 1;
		}
	}
	return v;
}

int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		long long x;
		scanf("%lld", &x);
		rmq[0][i] = make_pair(x, i);
	}
	for (int i = n + 1; i <= 2 * n; i++) {
		rmq[0][i] = make_pair(INF, 0);
	}
	build_rmq(n);
	for (int i = 1; i <= q; i++) {
		long long v;
		int l, r;
		scanf("%lld%d%d", &v, &l, &r);
		printf("%lld\n", query(v, l, r));
	}
	return 0;
}
