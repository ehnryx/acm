#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

/*
struct node { node *l, *r, *p; int key, cnt;
	node(int k=0);
  inline int dir() { return this == p->l; }
  inline void set_cld(node* c, bool left) { (left?l:r) = c; c->p = this; }
} _null, *null;
node::node(int k) { key=k; cnt=1;
  if (!null) { null=&_null; null->cnt=0; } l=r=p=null;}
namespace SplayTree {
//%%== Code for upwards propagating property (eg. count, min)
void update(node* x) { if (x != null) { x->cnt = 1 + x->l->cnt + x->r->cnt; } }
//%%== Core splay tree code (rotate, splay, delete)
inline void rot(node* x) { node *p = x->p; bool d = x->dir();
  p->set_cld(d ? x->r : x->l, d); p->p->set_cld(x, p->dir()); x->set_cld(p, !d);
  update(p); update(x); }
// splays node x until it is a child of node to
node* splay(node* x, node* to=null){ if(x!=null){ while(x->p!=to)if(x->p->p==to)
  rot(x); else { x->dir()==x->p->dir()?rot(x->p):rot(x); rot(x); }} return x; }
node* del(node* y) { node* x=splay(y)->r; if (x==null) x=y->l; else {
  while (x->l != null) { x=x->l; } splay(x,y)->set_cld(y->l,1); }
  x->p=null; update(x); return x; }
//%%== BST methods (lb, find, insert) (conflicts with other features, see above)
node* lb(node* c, ll k) { if (c == null) return c; // c MUST BE THE ROOT
  if(c->key>=k) { node* l=lb(c->l,k); return l==null?c:l; } return lb(c->r,k); }
node* lower_bound(node* ref, ll k) { return lb(splay(ref), k); }
node* insert(node* c, node* x) { if (splay(c) == null) return x;
  ll k=x->key; node* p; while(c!=null) { p=c; c=(p->key>k?p->l:p->r); }
  p->set_cld(x,p->key>k); return splay(x); }
//%%== Utility code (rank, nth order statistic) (requires count maintained)
int rank(node* x) { return splay(x)->l->cnt; } // for size, remove '->l'
}

struct Tree {
	node* root;
	Tree(): root(SplayTree::insert(null, new node(INF))) {}
	void insert(int v) {
		root = SplayTree::insert(root, new node(v));
	}
	int order_of_key(int v) {
		return SplayTree::rank(SplayTree::lower_bound(root, v));
	}
};
*/

const int N = 1<<18;
ordered_set<int> st[2*N];
//Tree st[2*N];
void insert(int x, int v) {
	st[x+=N].insert(v);
	for(x/=2;x;x/=2) {
		st[x].insert(v);
	}
}
int query(int l, int r, int v) {
	int res = 0;
	for(l+=N,r+=N;l<r;l/=2,r/=2) {
		if(l&1) res += st[l++].order_of_key(v);
		if(r&1) res += st[--r].order_of_key(v);
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	int a[n],b[n],c[n],inv[n+1],id[n];
	for(int i=0;i<n;i++) {
		cin>>a[i];
		inv[a[i]] = i;
	}
	for(int i=0;i<n;i++) {
		cin>>b[i];
		b[i] = inv[b[i]];
	}
	for(int i=0;i<n;i++) {
		cin>>c[i];
		c[i] = inv[c[i]];
		id[c[i]] = i;
	}

	ll ans = 0;
	for(int i=0;i<n;i++) {
		int j = id[b[i]];
		ans += query(0,j,b[i]);
		insert(j,b[i]);
	}
	cout<<ans<<nl;

	return 0;
}
