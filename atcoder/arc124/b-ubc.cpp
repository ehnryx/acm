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
struct node { pn l, r, p; int key, cnt; node(int k=0);
  inline int dir() { return this == p->r; }
  inline void setc(pn c, bool right) { (right?r:l) = c; c->p = this; }
} dat[1]; // nil = dat[0]
pn nil=[](){pn x=dat; x->l=x->r=x->p=x;
  x->cnt=0; return x;}();
node::node(int k): l(nil), r(nil), p(nil), key(k), cnt(1) {}
/*
int nodeid = 0; template <class... T> pn new_node(T&& ...args) {
  return &(dat[++nodeid] = node(forward<T>(args)...)); } */

namespace SplayTree {
//%%== Code for upwards propagating property (eg. count, min)
inline void pull(pn x) { if (x != nil) {
  x->cnt = 1 + x->l->cnt + x->r->cnt; }}
//%%== Core splay tree code (rotate, splay, delete)
inline void rot(pn x) { pn p = x->p; bool d=x->dir();
  p->setc(d ? x->l : x->r, d); p->p->setc(x, p->dir()); x->setc(p, !d);
  pull(p); pull(x); }
// splays node x until it is a child of node to
pn splay(pn x, pn to=nil) { if (x!=nil) { while (x->p!=to) {
  if (x->p->p!=to) rot(x->dir() == x->p->dir() ? x->p : x); rot(x); } }
  return x; }
pn del(pn y) { pn x=splay(y)->r; if (x==nil) x=y->l; else {
  while (x->l != nil) x = x->l; splay(x,y)->setc(y->l,0); }
  x->p=nil; pull(x); return x; }
//%%== BST methods (lb, find, insert) (conflicts with other features)
pn lb(pn c, int k) { if (c == nil) return c; // c MUST BE THE ROOT
  if (c->key>=k) { pn l=lb(c->l,k); return l==nil?c:l; }
  return lb(c->r,k); }
pn lowerBound(pn ref, int k) { return lb(splay(ref), k); }
pn find(pn c, int k) { c=lb(splay(c),k); return c->key!=k?nil:splay(c); }
pn insert(pn c, pn x) { if (splay(c)==nil) return x; int k=x->key; pn p;
  while (c!=nil) { p=c; c=(p->key>k?p->l:p->r); }
  p->setc(x,p->key<=k); return splay(x); }
//%%== Utility code (rank, nth order statistic; requires cnt maintained)
int idx(pn x) { return splay(x)->l->cnt; } // rank; for sz, remove '->l'
pn nth(pn c, int n) {splay(c); while(c!=nil) { int l=c->l->cnt;
  if (n==l) break; if (n < l) c = c->l; else n = n-l-1, c = c->r; }
  return c; }
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

  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  for(int i=0; i<n; i++) {
    cin >> b[i];
  }

  vector<int> ans;
  for(int i=0; i<n; i++) {
    int x = a.front() ^ b[i];
    pn root = nil;
    for(int j=0; j<n; j++) { root = SplayTree::insert(root, new node(b[j])); }
    root = SplayTree::del(SplayTree::find(root, b[i]));
    bool ok = true;
    for(int j=1; j<n; j++) {
      auto it = SplayTree::find(root, a[j] ^ x);
      if (it == nil) {
        ok = false;
        break;
      }
      root = SplayTree::del(it);
    }
    if(ok) {
      ans.push_back(x);
    }
  }

  sort(begin(ans), end(ans));
  ans.resize(unique(begin(ans), end(ans)) - begin(ans));
  cout << ans.size() << nl;
  for(int x : ans) {
    cout << x << nl;
  }

  return 0;
}
