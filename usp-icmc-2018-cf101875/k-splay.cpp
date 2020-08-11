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

struct node { node *l, *r, *p; int val, pre, suf, cnt, acc, lc, rc;
  node(int v=0);
  inline int dir() { return this == p->l; }
  inline void set_cld(node* c, bool left) { (left?l:r) = c; c->p = this; }
} _null, *null;
node::node(int v) { lc=rc=val=v; cnt=1; pre = suf = acc = 1;
  if (!null) {
		null=&_null; null->cnt=0; null->val=0;
		null->pre = null->suf = null->acc = 0;
		null->lc = null->rc = 0;
	}
	l=r=p=null;
}

namespace SplayTree {
	//%%== Code for upwards propagating property (eg. count, min)
	void update(node* x) {
		if (x != null) {
			x->lc = (x->l == null ? x->val : x->l->lc);
			x->rc = (x->r == null ? x->val : x->r->rc);
			x->cnt = x->l->cnt + 1 + x->r->cnt;
			x->acc = max(x->l->acc, x->r->acc);
			bool lefteq = (x->val == x->l->rc || x->l == null);
			bool righteq = (x->val == x->r->lc || x->r == null);
			if (lefteq && righteq) {
				x->acc = max(x->acc, x->l->suf + 1 + x->r->pre);
				x->pre = x->l->pre + (x->l->pre == x->l->cnt) * (1 + x->r->pre);
				x->suf = x->r->suf + (x->r->suf == x->r->cnt) * (1 + x->l->suf);
			} else if (lefteq) {
				x->acc = max(x->acc, x->l->suf + 1);
				x->pre = x->l->pre + (x->l->pre == x->l->cnt);
				x->suf = x->r->suf;
			} else if (righteq) {
				x->acc = max(x->acc, 1 + x->r->pre);
				x->pre = x->l->pre;
				x->suf = x->r->suf + (x->r->suf == x->r->cnt);
			} else {
				x->acc = max(x->acc, 1);
				x->pre = x->l->pre;
				x->suf = x->r->suf;
			}
		}
	}
	//%%== Code for downward lazy propagating property (eg. reverse subtree, add)
	void fix(node* x) {}
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
	//%%== Utility code (rank, nth order statistic) (requires count maintained)
	int rank(node* x) { return splay(x)->l->cnt; } // for size, remove '->l'
	node* nth(node* c, int n) { splay(c); while (c!=null) { fix(c); int l=c->l->cnt;
		if (n==l) break; if (n < l) c = c->l; else n = n-l-1, c = c->r; } return c; }
	//%%== Iterator-based access, returns null when iterator exhausted
	node*  begin(node*c){if(splay(c)!=null)while(fix(c),c->l!=null)c=c->l;return c;}
	node* rbegin(node*c){if(splay(c)!=null)while(fix(c),c->r!=null)c=c->r;return c;}
	node* prv(node* x) { if (splay(x)->l == null) return null; x = x->l;
		while (fix(x), x->r != null) x=x->r; return x; }
	node* nxt(node* x) { if (splay(x)->r == null) return null; x = x->r;
		while (fix(x), x->l != null) x=x->l; return x; }
	//%%== Iterator-based insert, does NOT work with BST code unless key sorted
	node* insertBefore(node* c, node* at, node* x){ // to insert "last", use at=null
		if(at==null){if(splay(c)!=null)rbegin(c)->set_cld(x,0);} else{node* p=prv(at);
		if(p==null)at->set_cld(x,1); else p->set_cld(x,0);} return splay(x);}
	//%%== Range query and update operations by iterator, range is EXCLUSIVE!
	void pUpdate(node* x, int v) { splay(x)->val = v; update(x); }
	//%%== Rope operations: split and merge, null = right end
	node* splitBefore(node* x){if(splay(x)==null)return null; fix(x); if(x->l!=null)
		fix(x->l); node* ret=x->l;x->l=x->l->p=null;update(ret);update(x);return ret;}
	node* append(node* ref, node* other) { if (splay(ref)==null) return other;
		if (splay(other)==null) return ref; node* x=splay(rbegin(ref)); fix(x);
		fix(other); x->set_cld(other,0); update(x->r); update(x); return x; }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, q;
	cin >> n >> q;

	vector<node*> root;
	for (int i=0; i<n; i++) {
		int s;
		cin >> s;
		node* cur = null;
		for (int j=0; j<s; j++) {
			int v;
			cin >> v;
			cur = SplayTree::append(cur, new node(v));
		}
		root.push_back(cur);
	}

	while (q--) {
		int t;
		cin >> t;
		if (t==1) {
			int l, r, s;
			cin >> l >> r >> s;
			--l; --r; --s;
			node* left = SplayTree::nth(root[s], l);
			node* right = SplayTree::nth(root[s], r);
#define UPDATE
#ifdef UPDATE
			/* pUpdate version */
			int lv = left->val;
			int rv = right->val;
			SplayTree::pUpdate(right, lv);
			SplayTree::pUpdate(left, rv);
#else
			/* split/append version */
			node* pre = SplayTree::splitBefore(left);
			node* mid = SplayTree::nxt(left);
			SplayTree::splitBefore(mid);
			mid = SplayTree::splitBefore(right);
			node* suf = SplayTree::nxt(right);
			SplayTree::splitBefore(suf);
			pre = SplayTree::append(pre, right);
			pre = SplayTree::append(pre, mid);
			pre = SplayTree::append(pre, left);
			root[s] = SplayTree::append(pre, suf);
#endif
		} else if (t==2) {
			int l, r;
			cin >> l >> r;
			--l; --r;
			root.push_back(SplayTree::append(root[l], root[r]));
		} else if (t==3) {
			int s;
			cin >> s;
			--s;
			int half = SplayTree::splay(root[s])->cnt/2;
			node* mid = SplayTree::nth(root[s], half);
			root.push_back(SplayTree::splitBefore(mid));
			root.push_back(mid);
		} else {
			int s;
			cin >> s;
			--s;
			cout << SplayTree::splay(root[s])->acc << nl;
		}
	}

	return 0;
}
