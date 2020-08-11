#include <bits/stdc++.h>
using namespace std;
#define FILENAME "journey"

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct segtree {
	vector<ll> t;
	int n, h;
	segtree(int sz) {
		h = 32 - __builtin_clz(sz);
		n = 1<<h;
		t = vector<ll>(n*2, INFLL);
	}
	void update(int l, int r, ll v) {
		for (l+=n, r+=n; l<r; l/=2, r/=2) {
			if (l%2) {
				t[l] = min(t[l], v);
				++l;
			}
			if (r%2) {
				--r;
				t[r] = min(t[r], v);
			}
		}
	}
	ll query(int x) {
		ll ans = INFLL;
		for (x+=n; x; x/=2) {
			ans = min(ans, t[x]);
		}
		return ans;
	}
};

const int N = 50500;

int n;
ll t;
ll p[N], q[N], d[N];

bool check(int r) {
	//cerr << " r = " << r << endl;
	segtree st(n+3);
	st.update(1, 2, 0);

	for (int i=1; i<n; ++i) {
		ll dpi = st.query(i);
		//cerr << "dp " << i << " = " << dpi << endl;

		int lo = i+1;
		int hi = min(n+1, i+r+1);
		st.update(lo, hi, dpi+d[i]);
	}

	ll req = st.query(n);
	//cerr << " FTIME " << req+n-1 << endl;
	return req+n-1 <= t;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
	cin >> n >> t;

	for (int i=1; i<=n-1; ++i) {
		cin >> p[i];
		q[i] = p[i];
	}
	for (int i=n-2; i>=1; --i) {
		q[i] = min(q[i], q[i+1]);
	}

	for (int i=2; i<n; ++i) {
		cin >> d[i];
	}

	int lo = 1, hi = n-1;
	while (lo<hi) {
		int m = (lo+hi)/2;
		bool possible = check(m);
		if (possible) {
			hi = m;
		} else {
			lo = m+1;
		}
	}

	cout << q[lo] << endl;

	return 0;
}
