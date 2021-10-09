#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct node; using pn = node*;
struct node { pn l, r, p; int val, cnt; bool rev;
  node(int v=0);  // pp is for LCT
  inline int dir() { return this == p->r; }
  inline void setc(pn c, bool right) { (right?r:l) = c; c->p = this; }
} dat[1]; // nil = dat[0]
pn nil=[](){pn x=dat; x->l=x->r=x->p=x; /*x->acc=INF;*/ // RMQ
  x->cnt=0; return x;}();
node::node(int v): l(nil), r(nil), p(nil), val(v), cnt(1), rev(0) {}
int nodeid = 0; template <class... T> pn new_node(T&& ...args) {
  return &(dat[++nodeid] = node(forward<T>(args)...)); }

namespace ST {
//%%== Code for upwards propagating property (eg. count, min)
inline void pull(pn x) { if (x != nil) {
  x->cnt = 1 + x->l->cnt + x->r->cnt;
  /*x->acc = min(x->l->acc, min(x->val, x->r->acc));*/ } }         //RMQ
//%%== Code for lazy propagating property (eg. reverse subtree, add)
void rev(pn x) { if (x != nil) { x->rev ^= 1; swap(x->l, x->r); } }
//inline void modifyNode(pn x, ll v) { if (x != nil) {
  ///*x->val += v; x->acc += v; x->lazy += v;*/ } }                  //RMQ
//inline void setpp(pn x, pn pp) { if(x!=nil) x->pp = pp; }  // LCT
inline void push(pn x) {
  if (x->rev) { rev(x->l); rev(x->r); x->rev=0; }                  //REV
  //setpp(x->l, x->pp); setpp(x->r, x->pp);  // LCT
  //modifyNode(x->l, x->lazy); modifyNode(x->r, x->lazy); x->lazy=0; RMQ
}
//%%== call pushTo before using node if ancestor may have unpushed lazy
void pushTo(pn c) { if (c->p != nil) pushTo(c->p); push(c); }
//%%== Core splay tree code (rotate, splay, delete)
inline void rot(pn x) { pn p = x->p; push(p); push(x); bool d=x->dir();
  p->setc(d ? x->l : x->r, d); p->p->setc(x, p->dir()); x->setc(p, !d);
  pull(p); pull(x); }
// splays node x until it is a child of node to
pn splay(pn x, pn to=nil) { if (x!=nil) { while (x->p!=to) {
  if (x->p->p!=to) rot(x->dir() == x->p->dir() ? x->p : x); rot(x); } }
  return x; }
pn del(pn y) { pn x=splay(y)->r; if (x==nil) x=y->l; else {
  while (push(x), x->l != nil) x = x->l; splay(x,y)->setc(y->l,0); }
  x->p=nil; pull(x); return x; }
//%%== Utility code (rank, nth order statistic; requires cnt maintained)
int idx(pn x) { return splay(x)->l->cnt; } // rank; for sz, remove '->l'
pn nth(pn c, int n) {splay(c); while(c!=nil) { push(c); int l=c->l->cnt;
  if (n==l) break; if (n < l) c = c->l; else n = n-l-1, c = c->r; }
  return c; }
//%%== Iterator-based access, returns nil when iterator exhausted
pn first(pn c) { if (splay(c) != nil)
  while (push(c), c->l != nil) c=c->l; return splay(c); }
pn last(pn c) { if (splay(c) != nil)
  while (push(c), c->r != nil) c=c->r; return splay(c); }
pn prv(pn x) { if (splay(x)->l == nil) return nil; x = x->l;
  while (push(x), x->r != nil) x = x->r; return x; }
pn nxt(pn x) { if (splay(x)->r == nil) return nil; x = x->r;
  while (push(x), x->l != nil) x = x->l; return x; }
//%%== Iterator-based insert, does NOT work with BST unless key sorted
pn insertBefore(pn c, pn at, pn x) { // to insert "last", use at=nil
  if (at==nil) { if (splay(c)!=nil) last(c)->setc(x,1); }
  else { pn p=prv(at); if (p==nil) at->setc(x,0); else p->setc(x,1); }
  return splay(x); }
//%%== Range query/update operations by iterator, range is EXCLUSIVE!
pn range(pn c, pn l, pn r) { if (l == nil) {
  if (r == nil) return splay(c); return splay(r)->l; }
  if (l == r) return nil; splay(l);
  if (r == nil) return l->r; return splay(r,l)->l;}
pn rev_range(pn c, pn l, pn r) {
  pn u = range(c, l, r); rev(u); return splay(u); }
//ll pQuery(pn x) { return splay(x)->val; }
//ll rQuery(pn c, pn l, pn r) { return range(c, l, r)->acc; }
//void pUpdate(pn x, ll v) { splay(x)->val += v; pull(x); }          //RMQ
//void rUpdate(pn c, pn l, pn r, ll v) {
  //pn u = range(c, l, r); modifyNode(u, v); splay(u); }
//%%== Rope operations: split and merge, nil = right end
pn splitBefore(pn x) { if (splay(x)==nil) return nil;
  push(x); if (x->l!=nil) push(x->l);
  pn ret=x->l; x->l=x->l->p=nil; pull(ret); pull(x); return ret; }
pn append(pn l, pn r) { if (splay(l) == nil) return r;
  if (splay(r) == nil) return l; pn x = splay(last(l)); push(x);
  push(r); x->setc(r,1); pull(x->r); pull(x); return x; }
}

void clear_tree(node* root) {
  if(root == nil) return;
  clear_tree(root->l);
  clear_tree(root->r);
  delete root;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    vector<int> perm(n+1), inv(n+1);
    for(int i=1; i<=n; i++) {
      cin >> perm[i];
      inv[perm[i]] = i;
    }

    vector<node*> hnode(n+1), vnode(n+1);
    node* hroot = new node(0);
    node* vroot = new node(0);
    for(int i=1; i<=n; i++) {
      hnode[i] = new node(perm[i]);
      vnode[i] = new node(inv[i]);
      hroot = ST::append(hroot, hnode[i]);
      vroot = ST::append(vroot, vnode[i]);
    }

    while(m--) {
      int t;
      cin >> t;
      if(t == 1) {
        int l, r;
        cin >> l >> r;
        node* left = ST::prv(ST::nth(hroot, l));
        node* right = ST::nxt(ST::nth(hroot, r));
        hroot = ST::rev_range(hroot, left, right);
      } else if(t == 2) {
        int l, r;
        cin >> l >> r;
        node* left = ST::prv(ST::nth(vroot, l));
        node* right = ST::nxt(ST::nth(vroot, r));
        vroot = ST::rev_range(vroot, left, right);
      } else if(t == 3) {
        int i, ai;
        cin >> i >> ai;
        n += 1; // new id
        hnode.push_back(new node(n));
        vnode.push_back(new node(n));
        hroot = ST::insertBefore(hroot, ST::nth(hroot, i), hnode.back());
        vroot = ST::insertBefore(vroot, ST::nth(vroot, ai), vnode.back());
      } else if(t == 4) {
        int i;
        cin >> i;
        int nid = ST::nth(hroot, i)->val;
        ST::pushTo(vnode[nid]);
        cout << ST::idx(vnode[nid]) << nl;
      } else if(t == 5) {
        int ai;
        cin >> ai;
        int nid = ST::nth(vroot, ai)->val;
        ST::pushTo(hnode[nid]);
        cout << ST::idx(hnode[nid]) << nl;
      } else {
        assert(false);
      }
    }

    //clear_tree(hroot);
    //clear_tree(vroot);
  }

  return 0;
}
