#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using vi = vector<int>;

const char nl = '\n';
const ll LINF = 0x3f3f3f3f3f3f3f3f;
typedef ll Data;
typedef ll Update;
/*
class Segtree { const int h, n; vector<Data> t; vector<Update> d; vector<bool> lazy_bit;
	void pull(Data& p, Data l, Data r) {
		p = max(l,r);
	}
	void update(Data& cur, Update val, int len) {
		cur += val;
	}
	void update_lazy(Update& cur, Update val, int len) {
		cur += val;
	}
	void calc(int p, int seg_len) { pull(t[p], t[p<<1], t[p<<1|1]); if (lazy_bit[p]) update(t[p], d[p], seg_len); }
	void apply(int p, Update value, int seg_len) { update(t[p], value, seg_len); if (p < n) {
		if (lazy_bit[p]) { update_lazy(d[p], value, seg_len); } else { d[p] = value, lazy_bit[p] = true; }}}
	void build(int l, int r) { int k = 2; for (l+=n, r+=n-1; l > 1; k <<= 1) { l>>=1, r >>= 1; for (int i = r; i >= l; --i) calc(i,k); }}
	void push(int l, int r) { int s = h, k = 1 << (h-1); for (l+= n, r +=n-1; s > 0; --s, k>>=1) { for (int i = l>>s; i <= r >> s; ++i) {
		if (lazy_bit[i]) { apply(i<<1, d[i], k); apply(i<<1|1, d[i], k); lazy_bit[i] = false; d[i] = 0; }}}}
	public:
	Segtree(int x) : h(32 - __builtin_clz(x)), n(1<<h), t(2*n), d(n), lazy_bit(n) {}
	void inc_range(int l, int r, ll value) { push(l, l+1); push(r-1, r); int l0 = l, r0 = r, k = 1; for (l+=n, r+=n; l < r; l>>=1, r>>=1, k<<=1) {
			if (l&1) { apply(l++, value, k); }
			if (r&1) { apply(--r, value, k); }
		}
		build(l0, l0+1); build(r0-1, r0);
	}
	ll get_max(int l, int r) { push(l, l+1); push(r-1, r); ll ans = -LINF;
		for (l+=n, r+=n; l<r; l >>=1, r >>= 1) {
			if (l&1) pull(ans, ans, t[l++]);
			if (r&1) pull(ans, ans, t[--r]);
		}
		return ans;
	}
};
*/

struct Segtree {
	static const int N = 1<<20;
	ll st[2*N], z[2*N];
	Segtree() {
		memset(st, 0, sizeof st);
		memset(z, 0, sizeof z);
	}
	void push(int i) {
		if(z[i]) {
			st[2*i] += z[i];
			st[2*i+1] += z[i];
			z[2*i] += z[i];
			z[2*i+1] += z[i];
			z[i] = 0;
		}
	}
	void pull(int i) {
		st[i] = max(st[2*i], st[2*i+1]);
	}
	void inc_range(int l, int r, ll v) {
		inc_range(l, r-1, v, 1, 0, N-1);
	}
	void inc_range(int l, int r, ll v, int i, int s, int e) {
		if(r<s || e<l) return;
		if(l<=s && e<=r) {
			st[i] += v;
			z[i] += v;
			return;
		}
		push(i);
		int m = (s+e)/2;
		inc_range(l, r, v, 2*i, s, m);
		inc_range(l, r, v, 2*i+1, m+1, e);
		pull(i);
	}
	ll get_max(int l, int r) {
		return get_max(l, r-1, 1, 0, N-1);
	}
	ll get_max(int l, int r, int i, int s, int e) {
		if(r<s || e<l) return -LINF;
		if(l<=s && e<=r) {
			return st[i];
		}
		push(i);
		int m = (s+e)/2;
		return max(get_max(l, r, 2*i, s, m), get_max(l, r, 2*i+1, m+1, e));
	}
};

const int N = 8e5 + 5;
// st.inc_range
// st.get_max

int xloc[N], yloc[N];
map<int, int> xrev, yrev;

ll l, r;

struct pt {
	ll x, y, cost;
};

struct op {
	ll x, y, cost, width;
	op() {}
	op(ll a, ll b, ll c, ll d) : x(a), y(b), cost(c), width(d) {}
};

int n;
pt pts[N];
vector<op> at[N];

inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if(S == T) return EOF;
	}
	return *S++;
}
template<typename T> inline void read(T&x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x*10 + c-'0';
	if (sgn) x = -x;
}

Segtree st;

int rcount;
int find(int x) {
	int lo = 1, hi = rcount;
	while (lo < hi) {
		int m = (lo+hi)/2;
		if (xloc[m] >= x) {
			hi = m;
		} else {
			lo = m+1;
		}
	}
	return lo;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//cin >> n >> l >> r;
	read(n); read(l); read(r);
	for (int i=1; i<=n; ++i) {
		//cin >> pts[i].x >> pts[i].y >> pts[i].cost;
		read(pts[i].x);
		read(pts[i].y);
		read(pts[i].cost);
		ll x = pts[i].x, y = pts[i].y;

		xrev[x+r+1] = -1;
		xrev[x+r] = -1;
		xrev[x+l] = -1;
		xrev[x+l-1] = -1;
		xrev[x-l+1] = -1;
		xrev[x-l] = -1;
		xrev[x-r] = -1;
		xrev[x-r-1] = -1;

		yrev[y+r+1] = -1;
		yrev[y+r] = -1;
		yrev[y+l] = -1;
		yrev[y+l-1] = -1;
		yrev[y-l+1] = -1;
		yrev[y-l] = -1;
		yrev[y-r] = -1;
		yrev[y-r-1] = -1;
	}

	int cc = 0;
	for (auto& p : xrev) {
		p.second = ++cc;
		xloc[cc] = p.first;
	}
	rcount = cc;
	cc = 0;
	for (auto& p : yrev) {
		p.second = ++cc;
		yloc[cc] = p.first;
	}
	int ycount = cc;

	for (int i=1; i<=n; ++i) {
		int y = pts[i].y, x = pts[i].x, cost = pts[i].cost;
		at[yrev[y-r]].emplace_back(x-r, y-r, cost, r*2);
		at[yrev[y-l+1]].emplace_back(x-(l-1), y-l+1, -cost, (l-1)*2);
		at[yrev[y+l]].emplace_back(x-(l-1), y+l, cost, (l-1)*2);
		at[yrev[y+r+1]].emplace_back(x-r, y+r+1, -cost, r*2);
	}

	ll ans = 0;

	for (int i=1; i<=ycount; ++i) {
		//cerr << " AT " << i << " = " << yloc[i] << endl;
		for (auto& o : at[i]) {
			int lo = find(o.x), hi = find(o.x+o.width+1);
			/*
			int lo = xrev.lower_bound(o.x)->second;
			//cerr << "   Q " << o.x << " -> " << o.x+o.width << endl;
			int hi = xrev.upper_bound(o.x+o.width)->second;
			*/
			//cerr << "   RANGE ADD " << lo << "->" << hi << " : " << o.cost << endl;
			st.inc_range(lo, hi, o.cost);
		}

		//cerr << "  RANGE QUERY " << st.get_max(0, rcount+1) << endl;
		ans = max(ans, st.get_max(0, rcount+1));
	}
	cout << ans << endl;
	return 0;
}

