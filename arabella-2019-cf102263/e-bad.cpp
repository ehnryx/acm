#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ostream& operator << (ostream& os, const pii& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}

struct Edge {
	int i, c;
};

struct Query {
	int a, b, c;
};

struct SegTree { int n; ll *segt; // EXAMPLE
	SegTree(int len) { n = 1<<(32-__builtin_clz(len));
		segt = new ll[2*n];
	}

	void update(int x, int v) {
		segt[x+=n] = v;
		for (x/=2; x>0; x/=2) {
			segt[x] = segt[2*x] + segt[2*x+1];
		}
	}
	ll get_sum(int l, int r) {
		ll res = 0;
		for (l+=n,r+=n+1; l<r; l/=2,r/=2) {
			if (l&1) res += segt[l++];
			if (r&1) res += segt[--r];
		}
		return res;
	}

	ll query(int l, int r, ll g) {
		int s = l;
		while (l<r) {
			int m = (l+r)/2;
			if (get_sum(s,m) < g) {
				l = m+1;
			} else {
				r = m;
			}
		}
		// now sum(s,l) >= g
		ll one = get_sum(s,l);
		ll two = get_sum(s,l-1);
		if (abs(one-g) < abs(two-g)) return one;
		else return two;
	}
};

namespace HLD {
	const int N = 2e5+1;
	SegTree* segt[N];
	vector<int> adj[N];
	int d[N], par[N], sub[N], sz[N], root[N], ch[N], pos[N]; int dn, cn;
	int dfs(int u, int p) { d[u] = d[par[u]=p]+1; sub[u] = 1;
		for (int x:adj[u]) if (x!=p) sub[u] += dfs(x,u); return sub[u]; }
	void hld(int u, int p) { if (dn == cn) { root[cn]=u; sz[cn++]=0; }
		pos[u] = sz[ch[u]=dn]++; int b=-1, c=-1;
		for (int x:adj[u]) if (x!=p && sub[x]>b) b=sub[c=x]; if (c!=-1) hld(c,u);
		for (int y:adj[u]) if (y!=p && y!=c) { dn++; hld(y,u); } }
	void build(int r) { d[0] = dn = cn = 0; dfs(r,0); hld(r,0);
		for (int i=0; i<cn; i++) segt[i] = new SegTree(sz[i]); }

	ll path_length(int a, int b) {
		ll len = 0;
		while (ch[a] != ch[b]) {
			if (d[root[ch[a]]] < d[root[ch[b]]]) { swap(a,b); }
			len += segt[ch[a]]->get_sum(0, pos[a]);
			a = par[root[ch[a]]];
		}
		if (pos[a] != pos[b]) {
			if (d[a] < d[b]) { swap(a,b); }
			len += segt[ch[a]]->get_sum(pos[b]+1, pos[a]);
		}
		return len;
	}

	ll query_path(int a, int b, ll tot) {
		ll half = tot/2;
		int sid = 0;
		ll sum[2];
		sum[0] = sum[1] = 0;
		while (ch[a] != ch[b]) {
			if (d[root[ch[a]]] < d[root[ch[b]]]) { swap(a,b); sid ^= 1; }
			ll cur = segt[ch[a]]->get_sum(0, pos[a]);
			sum[sid] += cur;
			if (sum[sid] >= half) {
				// this will do
				ll over = segt[ch[a]]->query(0, pos[a], sum[sid]-half);
				ll other = segt[ch[a]]->query(0, pos[a], sum[sid]-half-1);
				assert(over >= 0 && other >= 0);
				return min(
					max(sum[sid]-over, tot - (sum[sid]-over)),
					max(sum[sid]-other, tot - (sum[sid]-other))
				);
			}
			a = par[root[ch[a]]];
		}
		// last part should do
		if (pos[a] != pos[b]) {
			if (d[a] < d[b]) { swap(a,b); sid ^= 1; }
			//assert(half >= sum[sid] && half >= sum[sid^1]);
			ll over = segt[ch[a]]->query(pos[b]+1, pos[a], half-sum[sid^1]);
			ll other = segt[ch[a]]->query(pos[b]+1, pos[a], half+1-sum[sid^1]);
			assert(over >= 0 && other >= 0);
			return min(
				max(sum[sid^1]+over, tot - (sum[sid^1]+over)),
				max(sum[sid^1]+other, tot - (sum[sid^1]+other))
			);
		}
		//assert(tot == 0);
		return 0;
	}

	void insert_node(int x, int v) {
		segt[ch[x]]->update(pos[x], v);
	}
}

const int N = 2e5+1;
vector<Edge> adj[N];
int par[N], pcost[N];
// values
int bestd[N], secd[N], bestc[N];
ll dp1[N], sec[N], third[N], dp2[N], cdp2[N], csec[N], up1[N], up2[N];
// endpoints
int ldp1[N], lsec[N], lthird[N], lup1[N];
pii ldp2[N], lup2[N], lcdp2[N], lcsec[N];

ll path_down(int u, int p = -1) {
	if (dp1[u] != -1) return dp1[u];
	if (p != -1) par[u] = p;
	ll res = 0;
	ldp1[u] = lsec[u] = lthird[u] = u;
	for (const Edge& e : adj[u]) {
		if (e.i != par[u]) {
			pcost[e.i] = e.c;
			ll path = e.c + path_down(e.i, u);
			if (path > res) {
				secd[u] = bestd[u];
				sec[u] = res;
				lsec[u] = ldp1[u];
				bestd[u] = e.i;
				res = path;
				ldp1[u] = ldp1[e.i];
			} else if (path > sec[u]) {
				third[u] = sec[u];
				lthird[u] = lsec[u];
				secd[u] = e.i;
				sec[u] = path;
				lsec[u] = ldp1[e.i];
			} else if (path > third[u]) {
				third[u] = path;
				lthird[u] = ldp1[e.i];
			}
		}
	}
	return dp1[u] = res;
}

ll solve_down(int u) {
	if (dp2[u] != -1) return dp2[u];
	ll res = dp1[u] + sec[u];
	ldp2[u] = pii(ldp1[u], lsec[u]);
	for (const Edge& e : adj[u]) {
		if (e.i != par[u]) {
			ll path = solve_down(e.i);
			if (path > res) {
				res = path;
				ldp2[u] = ldp2[e.i];
			}
			if (path > cdp2[u]) {
				csec[u] = cdp2[u];
				lcsec[u] = lcdp2[u];
				cdp2[u] = path;
				bestc[u] = e.i;
				lcdp2[u] = ldp2[e.i];
			} else if (path > csec[u]) {
				csec[u] = path;
				lcsec[u] = ldp2[e.i];
			}
		}
	}
	return dp2[u] = res;
}

ll path_up(int u) {
	if (up1[u] != -1) return up1[u];
	ll res = -INFLL;
	if (par[u]) {
		ll cur = pcost[u] + path_up(par[u]);
		if (cur > res) {
			res = cur;
			lup1[u] = lup1[par[u]];
		}
		if (bestd[par[u]] == u) {
			ll path = pcost[u] + sec[par[u]];
			if (path > res) {
				res = path;
				lup1[u] = lsec[par[u]];
			}
		} else {
			ll path = pcost[u] + dp1[par[u]];
			if (path > res) {
				res = path;
				lup1[u] = ldp1[par[u]];
			}
		}
	}
	up1[u] = res;
	for (const Edge& e : adj[u]) {
		if (e.i != par[u]) {
			path_up(e.i);
		}
	}
	return up1[u];
}

ll solve_up(int u) {
	if (up2[u] != -1) return up2[u];
	ll res = -INFLL;
	if (par[u]) {
		ll cur = solve_up(par[u]);
		if (cur > res) {
			res = cur;
			lup2[u] = lup2[par[u]];
		}
		// weird
		if (bestc[par[u]] == u) {
			ll path = csec[par[u]];
			if (path > res) {
				res = path;
				lup2[u] = lcsec[par[u]];
			}
		} else {
			ll path = cdp2[par[u]];
			if (path > res) {
				res = path;
				lup2[u] = lcdp2[par[u]];
			}
		}
		// up
		if (bestd[par[u]] == u) {
			ll path = path_up(par[u]) + sec[par[u]];
			if (path > res) {
				res = path;
				lup2[u] = pii(lup1[par[u]], lsec[par[u]]);
			}
		} else {
			ll path = path_up(par[u]) + dp1[par[u]];
			if (path > res) {
				res = path;
				lup2[u] = pii(lup1[par[u]], ldp1[par[u]]);
			}
		}
		// down
		if (bestd[par[u]] == u) {
			ll path = sec[par[u]] + third[par[u]];
			if (path > res) {
				res = path;
				lup2[u] = pii(lsec[par[u]], lthird[par[u]]);
			}
		} else if (secd[par[u]] == u) {
			ll path = dp1[par[u]] + third[par[u]];
			if (path > res) {
				res = path;
				lup2[u] = pii(ldp1[par[u]], lthird[par[u]]);
			}
		} else {
			ll path = dp1[par[u]] + sec[par[u]];
			if (path > res) {
				res = path;
				lup2[u] = pii(ldp1[par[u]], lsec[par[u]]);
			}
		}
	}
	up2[u] = res;
	for (const Edge& e : adj[u]) {
		if (e.i != par[u]) {
			solve_up(e.i);
		}
	}
	return up2[u];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	memset(dp1, -1, sizeof dp1);
	memset(dp2, -1, sizeof dp2);
	memset(up1, -1, sizeof up1);
	memset(up2, -1, sizeof up2);

	int n;
	cin >> n;

	vector<Query> edges;
	For(i,n-1) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
		edges.push_back({a,b,c});
		HLD::adj[a].push_back(b);
		HLD::adj[b].push_back(a);
	}

	path_down(1, 0);
	solve_down(1);
	path_up(1);
	solve_up(1);

	HLD::build(1);
	FOR(i,1,n) {
		HLD::insert_node(i, pcost[i]);
	}

//#define DEBUG
#ifdef DEBUG
	FOR(i,1,n) {
		//cerr << i << ": pd, sd, pu, su::  " << path_down(i) << " " << solve_down(i) << " " << path_up(i) << " " << solve_up(i) << " " << cdp2[i] << nl;
		//cerr << " paths: " << "  ldp2 " << ldp2[i] << "  lup2 " << lup2[i] << "  lcdp2 " << lcdp2[i] << nl;
	}
#endif

	for (const Query& it : edges) {
		int a = it.a;
		int b = it.b;
		int c = it.c;
		//cerr << nl << " answering " << a << " " << b << " " << c << nl;
		if (a == par[b]) swap(a,b);
		ll dlen = solve_down(a);
		ll ulen = solve_up(a);
		ll ans = max(ulen, dlen);
		int da, db, ua, ub;
		tie(da,db) = ldp2[a];
		tie(ua,ub) = lup2[a];
		//cerr << "down: " << da << " " << db << " -> " << dlen << nl;
		//cerr << "query_path: " << HLD::query_path(da,db,dlen) << nl;
		//cerr << "uown: " << ua << " " << ub << " -> " << ulen << nl;
		//cerr << "query_path: " << HLD::query_path(ua,ub,ulen) << nl;
		//assert(da && db || !da && !db);
		//assert(ua && ub || !ua && !ub);
		//assert(dlen == HLD::path_length(da,db));
		//assert(ulen == HLD::path_length(ua,ub));
		ans = max(ans, HLD::query_path(da,db,dlen) + c + HLD::query_path(ua,ub,ulen));
		cout << ans << nl;
	}

	return 0;
}
