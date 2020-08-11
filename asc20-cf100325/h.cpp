//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "rmq"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e5 + 7;

struct node; using pn = node*;
struct node {
  pn l, r, p; int cnt, val, acc;
  node(int v=0);
  inline int dir() { return this == p->r; }
  inline void setc(pn c, bool right) { (right?r:l) = c; c->p = this; }
} dat[N];
pn nil = []() {
  pn x = dat; x->l = x->r = x->p = x; x->acc = INF;
  x->cnt = 0; return x;
} ();
node::node(int v): l(nil), r(nil), p(nil),
  cnt(1), val(v), acc(v) {}
int nodeid = 0; template <class... T> pn new_node(T&& ...args) {
  return &(dat[++nodeid] = node(forward<T>(args)...)); }

namespace SplayTree {
  inline void pull(pn x) { if(x != nil) {
    x->cnt = 1 + x->l->cnt + x->r->cnt;
    x->acc = min(x->l->acc, min(x->val, x->r->acc));
  }}
  inline void rot(pn x) {
    pn p = x->p; bool d=x->dir();
    p->setc(d ? x->l : x->r, d); p->p->setc(x, p->dir()); x->setc(p, !d);
    pull(p); pull(x);
  }
  pn splay(pn x, pn to=nil) {
    if(x!=nil) { while(x->p != to) {
        if (x->p->p != to) rot(x->dir() == x->p->dir() ? x->p : x);
        rot(x); } }
    return x;
  }
  pn nth(pn c, int n) {
    splay(c); while(c!=nil) { int l=c->l->cnt;
    if(n == l) break; if (n<l) c=c->l; else n = n-l-1, c=c->r; }
    return c;
  }
  pn last(pn c) { if(splay(c) != nil) while(c->r != nil) c = c->r;
    return splay(c); }
  pn prv(pn x) { if(splay(x)->l == nil) return nil;
    x = x->l;
    while(x->r != nil) x = x->r;
    return x;
  }
  pn insertBefore(pn c, pn at, pn x) {
    if(at == nil) { if(splay(c)!=nil) last(c)->setc(x,1); }
    else { pn p = prv(at); if(p == nil) at->setc(x, 0); else p->setc(x, 1); }
    return splay(x);
  }
  pn range(pn c, pn l, pn r) { if(l == nil) {
    if(r == nil) return splay(c); else return splay(r)->l; }
    if(l == r) return nil; else splay(l);
    if(r == nil) return l->r; else return splay(r,l)->l;
  }
  int rQuery(pn c, pn l, pn r) { return range(c, l, r)->acc; }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  pn root = nil;
  while(n--) {
    char t;
    cin >> t;
    if(t == '+') {
      int i, x;
      cin >> i >> x;
      pn at = SplayTree::nth(root, i);
      root = SplayTree::insertBefore(root, at, new_node(x));
    } else {
      int l, r;
      cin >> l >> r;
      pn left = SplayTree::prv(SplayTree::nth(root, l-1));
      pn right = SplayTree::nth(root, r);
      cout << SplayTree::rQuery(root, left, right) << nl;
    }
  }

  return 0;
}
