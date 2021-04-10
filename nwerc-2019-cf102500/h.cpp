#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const ll INF = 0x3f3f3f3f3f3f3f3f;
const ld EPS = 1e-9;

struct Segtree {
	vector<ll> t;
	int n, h;
	Segtree() {}
	Segtree (int sz) {
		h = 32-__builtin_clz(sz);
		n = 1<<h;
		t = vector<ll>(n<<1, -INF);
	}
	void clear() {
		for (int i=0; i<(n<<1); ++i) {
			t[i] = -INF;
		}
	}
	int bs(int l, int r, ll lim, int x, int lv, int rv) {
		if (r<=lv || rv<=l) {
			return -1;
		}
		if (t[x] < lim) {	// TODO epsilons
			return -1;
		}
		if (rv-lv == 1) {
			return lv;
		}
		int mv = (lv+rv)/2;
		int res = bs(l, r, lim, x*2+1, mv, rv);
		if (res != -1) {
			return res;
		}
		return bs(l, r, lim, x*2, lv, mv);
	}
	int bs(int l, int r, ll lim) {
		return bs(l, r, lim, 1, 0, n);
	}
	void assign(int x, ll v) {
		x+=n;
		t[x] = v;
		for (x/=2; x; x/=2) {
			t[x] = max(t[x<<1], t[x<<1|1]);
		}
	}
};


void test_segtree() {
	int n;
	cin >> n;
	Segtree st(n+1);
	vector<int> a(n+1);
	for (int i=1; i<=n; ++i) {
		int x;
		cin >> x;
		st.assign(i, x);
		a[i] = x;
	}
	int k;
	cin >> k;
	for (int i=1; i<=k; ++i) {
		int l, r;
		cin >> l >> r;
		cout << st.bs(l, r, a[l]) << "\n";
	}
}

int n, k;
Segtree st;

ld solve(vector<int>& h, ll g) {
	st.clear();
	for (int i=0; i<=n; ++i) {
		st.assign(i, h[i]+g*i);
	}
	ld ans = 0;
	for (int i=0; i<n; ++i) {
		ll q = h[i]+g*i;
		int fin = st.bs(i, n+1, q);
		ld cur = fin-i;
		if (fin < n) {
			ll ff = h[fin]+g*fin;
			ll fg = h[fin+1]+g*(fin+1);
			//cerr << "      ! " << ff << " " << fg << endl;
			assert(ff >= q);
			assert(fg <= q);
			cur += (ld) (ff-q)/(ff-fg);
		}
		ans = max(ans, cur);
	}
	return ans;
}

vector<int> h;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	h = vector<int>(n+1);
	for (int i=0; i<=n; ++i) {
		cin >> h[i];
	}
	st = Segtree(n+5);
	cout << fixed << setprecision(10);
	for (int qq=0; qq<k; ++qq) {
		ld gl;
		cin >> gl;
		ll g = round(-10*gl);
		//cerr << " G " << g << endl;
		ld ans = solve(h, g);
		//cerr << " :: " << ans << endl;
		reverse(h.begin(), h.end());
		for (int i=0; i<=n; ++i) {
			h[i] *= -1;
		}

		ans = max(solve(h, g), ans);
		//cerr << " :: " << ans << endl;
		reverse(h.begin(), h.end());
		for (int i=0; i<=n; ++i) {
			h[i] *= -1;
		}

		if (ans > EPS) {
			cout << ans << "\n";
		} else {
			cout << -1 << "\n";
		}
	}

	return 0;
}
