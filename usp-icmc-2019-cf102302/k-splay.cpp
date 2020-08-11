#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
inline void readll(ll &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

struct node { node *l, *r, *p; ll key, cnt;
	node(ll k=0);
	inline int dir() { return this == p->l; }
	inline void set_cld(node* c, bool left) { (left?l:r) = c; c->p = this; }
} _null, *null;
node::node(ll k) { key=k; cnt=1;
	if (!null) { null=&_null; null->cnt=0; } l=r=p=null;
}
namespace SplayTree {
	//%%== Code for upwards propagating property (eg. count, min)
	void update(node* x) { if (x != null) { x->cnt = 1 + x->l->cnt + x->r->cnt;
		/*x->acc = min(x->l->acc, min(x->val, x->r->acc));*/ } }                 //RMQ
	//%%== Code for downward lazy propagating property (eg. reverse subtree, add)
	void modifyNode(node* x, ll v) { }
	void fix(node* x) { }
	//%%== Core splay tree code (rotate, splay, delete)
	inline void rot(node* x) { node *p = x->p; fix(p), fix(x); bool d = x->dir();
		p->set_cld(d ? x->r : x->l, d); p->p->set_cld(x, p->dir()); x->set_cld(p, !d);
		update(p); update(x); }
	// splays node x until it is a child of node to
	node* splay(node* x, node* to=null){ if(x!=null){ while(x->p!=to)if(x->p->p==to)
		rot(x); else { x->dir()==x->p->dir()?rot(x->p):rot(x); rot(x); }} return x; }
	node* del(node* y) { node* x=splay(y)->r; if (x==null) x=y->l; else {
		while (fix(x), x->l != null) x = x->l; splay(x,y)->set_cld(y->l,1); }
	x->p=null; update(x); return x; }
	//%%== BST methods (lb, find, insert) (conflicts with other features, see above)
	node* lb(node* c, ll k) { if (c == null) return c; fix(c); // c MUST BE THE ROOT
		if(c->key>=k) { node* l=lb(c->l,k); return l==null?c:l; } return lb(c->r,k); }
	node* lower_bound(node* ref, ll k) { return lb(splay(ref), k); }
	node* find(node* c, ll k) { c=lb(splay(c),k); return c->key!=k?null:splay(c); }
	node* insert(node* c, node* x) { if (splay(c) == null) return x;
		ll k=x->key; node* p; while(c!=null) { fix(c); p=c; c=(p->key>k?p->l:p->r); }
		p->set_cld(x,p->key>k); return splay(x); }
	//%%== Utility code (rank, nth order statistic) (requires count maintained)
	int rank(node* x) { return splay(x)->l->cnt; } // for size, remove '->l'
	int size(node* x) { return splay(x)->cnt; } // for size, remove '->l'
	node* nth(node* c, int n) { splay(c); while (c!=null) { fix(c); int l=c->l->cnt;
		if (n==l) break; if (n < l) c = c->l; else n = n-l-1, c = c->r; } return c; }
	//%%== Iterator-based access, returns null when iterator exhausted
	node*  begin(node*c){if(splay(c)!=null)while(fix(c),c->l!=null)c=c->l;return c;}
	node* rbegin(node*c){if(splay(c)!=null)while(fix(c),c->r!=null)c=c->r;return c;}
	node* prv(node* x) { if (splay(x)->l == null) return null; x = x->l;
		while (fix(x), x->r != null) x=x->r; return x; }
	node* nxt(node* x) { if (splay(x)->r == null) return null; x = x->r;
		while (fix(x), x->l != null) x=x->l; return x; }
}

// get_sarray()[i] = idx of suffix s[i..L-1] in list of sorted suffixes
struct suff_array {
	const int L; vi s; int i, skip, lvl;
	vector<vi> P; vector<pair<pii,int>> M;
	suff_array(const vi &s) : L(s.size()), s(s), P(1, vi(L, 0)), M(L) {
		for (i = 0; i < L-(L==1); i++) P[0][i] = s[i];
		for (skip = 1, lvl = 1; skip < L; skip *= 2, lvl++) {
			P.push_back(vi(L, 0));
			for (int i = 0; i < L; i++)
				M[i] = {{P[lvl-1][i], i+skip<L ? P[lvl-1][i + skip] : -1000}, i};
			sort(M.begin(), M.end());
			for (int i = 0; i < L; i++)
				P[lvl][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ?
					P[lvl][M[i-1].second] : i; } }
	const vi& get_sarray() { return P.back(); }
	//returns len of longest common prefix of s[i...L-1] and s[j...L-1], O(lg L)
	int lcp(int i, int j) {
		int len = 0; if (i == j) return L - i;
		for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--)
			if (P[k][i] == P[k][j]) { i += 1 << k; j += 1 << k; len += 1 << k; }
		return len; }
};

const int N = 1<<19;
node* st[2*N];
void insert(int x, ll v) {
	for(x+=N;x;x/=2) {
		st[x] = SplayTree::insert(st[x], new node(v));
	}
}
int query_node(node* r, ll lb, ll ub) {
	int res = 0;
	node* ubx = SplayTree::lower_bound(r,ub+1);
	res += (ubx==null ? SplayTree::size(r) : SplayTree::rank(ubx));
	node* lbx = SplayTree::lower_bound(r,lb);
	res -= (lbx==null ? SplayTree::size(r) : SplayTree::rank(lbx));
	return res;
}
int query(int l, int r, ll lb, ll ub) {
	int res = 0;
	for(l+=N,r+=N;l<r;l/=2,r/=2) {
		if(l&1) res += query_node(st[l++],lb,ub);
		if(r&1) res += query_node(st[--r],lb,ub);
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	fill(st,st+2*N,null);

	int n; ll left,right;
	//cin>>n>>left>>right;
	read(n);readll(left);readll(right);
	vector<int> a(n);
	ll cur = 0;
	for(int i=0;i<n;i++) {
		//cin>>a[i];
		read(a[i]);
		insert(i,cur+=a[i]);
	}

	suff_array sa(a);
	auto& id = sa.get_sarray();
	int rev[n];
	for(int i=0;i<n;i++) {
		rev[id[i]]=i;
	}

	ll ans = 0;
	set<int> idx;
	for(int i=cur=0;i<n;i++) {
		int pre = 0;
		auto it = idx.lower_bound(id[i]);
		if(it!=idx.end()) pre = max(pre,sa.lcp(i,rev[*it]));
		if(it!=idx.begin()) pre = max(pre,sa.lcp(i,rev[*prev(it)]));
		idx.insert(id[i]);
		ans += query(i+pre,n,left+cur,right+cur);
		cur += a[i];
	}
	cout<<ans<<nl;

	return 0;
}
