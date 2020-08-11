#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("ipa-pta")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef int ll;

const char nl = '\n';
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
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

const int N = 4e5+1;

//! THANKS JASON!
//!
struct node { node *l, *r, *p; ll val, id, cnt, lazy; node* key;
  node(node* k=0, ll v=0, ll i=0);
  inline int dir() { return this == p->l; }
  inline void set_cld(node* c, bool left) { (left?l:r) = c; c->p = this; }
} _null, *null, data[2*N];
node::node(node* k, ll v, ll i) { key=k; val=v; id=i; cnt=1; lazy=0; 
  if (!null) { null=&_null; null->cnt=0; } l=r=p=null;} //RMQ
namespace SplayTree {
//%%== Code for upwards propagating property (eg. count, min)
void update(node* x) { if (x != null) { x->cnt = 1 + x->l->cnt + x->r->cnt; } }
//%%== Code for downward lazy propagating property (eg. reverse subtree, add)
void modifyNode(node* x, ll v) { if (x != null) { x->val += v; x->lazy += v; } }
node* fix(node* x) {
  modifyNode(x->l, x->lazy); modifyNode(x->r, x->lazy); x->lazy=0; return x; }   //RMQ
//%%== Core splay tree code (rotate, splay, delete)
inline void rot(node* x) { node *p = x->p; fix(p), fix(x); bool d = x->dir();
  p->set_cld(d ? x->r : x->l, d); p->p->set_cld(x, p->dir()); x->set_cld(p, !d);
  update(p); update(x); }
// splays node x until it is a child of node to
node* splay(node* x, node* to=null){ if(x!=null){ while(x->p!=to)if(x->p->p==to)
  rot(x); else { x->dir()==x->p->dir()?rot(x->p):rot(x); rot(x); }} return x; }

//%%== call fixDownTo() before using node if an ancestor may have un-pushed lazy
// TODO ???????
//node* fixDownTo(node* c) { if (c != null) { if (c->p != null) fixDownTo(c->p); fix(c); } return c; }
//inline node* fixDownTo(node* c) { return rng()%3 ? splay(c) : c; }
//inline node* fixDownTo(node* c) { return rng()%2 ? splay(c) : fixDown2(c); }
inline node* fixDownTo(node* c) { return splay(c); }

//%%== BST methods (lb, find, insert) (conflicts with other features, see above)
node* lb(node* c, ll k) { if (c == null) return c; //fix(c); // c MUST BE THE ROOT
  if(fixDownTo(c->key)->val>=k) { node* l=lb(c->l,k); return l==null?c:l; } return lb(c->r,k); }
node* lower_bound(node* ref, ll k) { return splay(lb(splay(ref), k)); }
//%%== Utility code (rank, nth order statistic) (requires count maintained)
int rank(node* x) { return splay(x)->l->cnt; } // for size, remove '->l'
node* nth(node* c, int n) { splay(c); while (c!=null) { fix(c); int l=c->l->cnt;
  if (n==l) break; if (n < l) c = c->l; else n = n-l-1, c = c->r; } return splay(c); }
//%%== Iterator-based access, returns null when iterator exhausted
node*  begin(node*c){if(splay(c)!=null)while(fix(c),c->l!=null)c=c->l;return c;}
node* prv(node* x) { if (splay(x)->l == null) return null; x = x->l;
  while (fix(x), x->r != null) x=x->r; return x; }
node* nxt(node* x) { if (splay(x)->r == null) return null; x = x->r;
  while (fix(x), x->l != null) x=x->l; return x; }
//%%== Iterator-based insert, does NOT work with BST code unless key sorted
node* insertBefore(node* c, node* at, node* x){ // to insert "last", use at=null
  if(at==null){if(splay(c)!=null)rbegin(c)->set_cld(x,0);} else{node* p=prv(at);
  if(p==null)at->set_cld(x,1); else p->set_cld(x,0);} return splay(x);}
//%%== Range query and update operations by iterator, range is EXCLUSIVE!
node* rGet(node* c, node* l, node* r){ if(l==null){ if(r==null) return splay(c);
  return splay(r)->l; } splay(l); if(r==null)return l->r; return splay(r,l)->l;}
void rUpdate(node* c, node* l, node* r, ll v) {
  node* u = rGet(c, l, r); modifyNode(u, v); splay(u); }
}
////////////////////////////////////////////////////////////////////////////////

node* root[N];

int main() {
	int n;
	//cin >> n;
	read(n);

	fill(root, root+n+1, null);

	node* ans = null;

	int did = 0;

	For(i,n) {
		int c, a;
		//cin >> c >> a;
		read(c); read(a);

		node* w = (a == 0 ? null : (a >= i ? SplayTree::begin(root[c]) : SplayTree::lower_bound(root[c], i-a-1)));
		node* obj = new (&data[did]) node(0,0,i+1);
		node* cur = new (&data[N+did++]) node(obj,0);
		if (w == null) {
			obj->val = i;
			ans = SplayTree::insertBefore(ans, null, obj);
			root[c] = SplayTree::insertBefore(root[c], null, cur);
		} else {
			SplayTree::splay(w->key);
			if (w->key->val == i-a-1) {
				obj->val = w->key->val+1;
				ans = SplayTree::insertBefore(ans, SplayTree::nxt(w->key), obj);
				SplayTree::rUpdate(ans, obj, null, 1);
				root[c] = SplayTree::insertBefore(w, SplayTree::nxt(w), cur);
			} else {
				obj->val = w->key->val;
				ans = SplayTree::insertBefore(ans, w->key, obj);
				SplayTree::rUpdate(ans, obj, null, 1);
				root[c] = SplayTree::insertBefore(w, w, cur);
			}
		}

//#define DEBUG
#ifdef DEBUG
		cout << "after " << i << " -> ";
		for (node* it=SplayTree::begin(ans); it!=null; it=SplayTree::nxt(it)) {
			cout << it->id << " ";
		}
		cout << nl;
		for (int j=1; j<=3; j++) {
			cout << "TEAM " << j << " -> ";
			for (node* it=SplayTree::begin(root[j]); it!=null; it=SplayTree::nxt(it)) {
				cout << it->key->val << " ";
			}
			cout << nl;
		}
		cout << nl;
#endif
	}

	for (node* it=SplayTree::begin(ans); it!=null; it=SplayTree::nxt(it)) {
		printf("%d ", it->id);
	}
	putchar('\n');

	return 0;
}
