#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

ll egcd(ll a, ll b, ll& x, ll& y) {
	if (!b) { x = 1; y = 0; return a; }
	ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d;
}

ll add(ll x, ll y, ll m) {
	x += y;
	if (x >= m) x -= m;
	return x;
}

ll mul(ll x, ll y, ll m) {
	return add((x * y - (ll) ((ld) x / m * y) * m) % m, m, m);
}

bool chin_rem(ll a1, ll m1, ll a2, ll m2, ll& A, ll& M) {
	ll X1, X2, d = egcd(m1, m2, X1, X2); if (a1 % d != a2 % d) return 0;
	M = m1/d*m2; A = add((mul(mul(X1,(a2/d),m2),m1,M) + mul(mul(X2,(a1/d),m1),m2,M) + a1%d)%M, M, M);
	return 1; }

struct val {
	ll a, m;
	val(): a(0), m(1) {}
	val(ll x, ll y): a(x), m(y) {}
	friend val merge(const val& a, const val& b) {
		if (a.a == -1 || b.a == -1) return {-1, -1};
		val ret;
		if (!chin_rem(a.a, a.m, b.a, b.m, ret.a, ret.m)) {
			ret = {-1, -1};
		}
		return ret;
	}
};

const int N = 201;

struct segt {
	vector<val> t;
	segt(): t(2*N) {}
	void build() {
		for (int i = N-1; i >= 1; i--) {
			t[i] = merge(t[2*i], t[2*i+1]);
		}
	}
	val query(int l, int r) {
		val ans;
		for (l += N, r += N+1; l < r; l /= 2, r /= 2) {
			if (l%2) ans = merge(ans, t[l++]);
			if (r%2) ans = merge(ans, t[--r]);
		}
		return ans;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T; cin >> T;
	for (int tt = 1; tt <= T; tt++) {
		cout << "Case #" << tt << ":\n";
		int n, m; cin >> n >> m;
		vector<vector<val>> grid(n, vector<val>(m)); 
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> grid[i][j].a;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> grid[i][j].m;
			}
		}
		vector<vector<vector<val>>> vals(n, vector<vector<val>>(m));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				val cur;
				vals[i][j].resize(m - j);
				for (int k = j; k < m; k++) {
					cur = merge(cur, grid[i][k]);
					vals[i][j][k-j] = cur;
				}
			}
		}
		vector<vector<segt>> segs(m);
		for (int i = 0; i < m; i++) {
			segs[i].resize(m - i);
			for (int j = i; j < m; j++) {
				for (int k = 0; k < n; k++) {
					segs[i][j-i].t[N+k] = vals[k][i][j-i];
				}
				segs[i][j-i].build();
			}
		}
		int q; cin >> q;
		while (q--) {
			int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2; x1--; y1--; x2--; y2--;
			cout << segs[y1][y2-y1].query(x1, x2).a << nl;
		}
	}

	return 0;
}
