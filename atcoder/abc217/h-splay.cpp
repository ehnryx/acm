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

const int N = 1e6;

struct node; using pn = node*;
struct node { pn l, r, p; int key, val, cnt, lazy_key, lazy_val;
  node(int k=0, int v=0);
  inline int dir() { return this == p->r; }
  inline void setc(pn c, bool right) { (right?r:l) = c; c->p = this; }
} dat[N];
pn nil=[](){pn x=dat; x->l=x->r=x->p=x;
  x->cnt=0; return x;}();
node::node(int k, int v): l(nil), r(nil), p(nil),
  key(k), val(v), cnt(1), lazy_key(0), lazy_val(v) {}
int nodeid = 0; template <class... T> pn new_node(T&& ...args) {
  return &(dat[++nodeid] = node(forward<T>(args)...)); }

namespace ST {
//%%== Code for upwards propagating property (eg. count, min)
inline void pull(pn x) { if (x != nil) {
  x->cnt = 1 + x->l->cnt + x->r->cnt; } }
//%%== Code for lazy propagating property (eg. reverse subtree, add)
inline void modifyNode(pn x, int k, int v) { if (x != nil) {
  x->key += k; x->lazy_key += k;
  x->val += v; x->lazy_val += v; } }
inline void push(pn x) {
  modifyNode(x->l, x->lazy_key, x->lazy_val);
  modifyNode(x->r, x->lazy_key, x->lazy_val);
  x->lazy_key = x->lazy_val = 0;
}
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
//%%== BST methods (lb, find, insert) (conflicts with other features)
pn lb(pn c, int k) { if (c == nil) return c; // c MUST BE THE ROOT
  push(c); if (c->key>=k) { pn l=lb(c->l,k); return l==nil?c:l; }
  return lb(c->r,k); }
pn lower_bound(pn ref, int k) { return lb(splay(ref), k); }
pn lb_val(pn c, int v) { if (c == nil) return c;
  push(c); if (c->val>=v) { pn l=lb_val(c->l,v); return l==nil?c:l; }
  return lb_val(c->r,v); }
pn lower_bound_val(pn ref, int v) { return lb_val(splay(ref), v); }
pn find(pn c, int k) { c=lb(splay(c),k); return c->key!=k?nil:splay(c); }
pn insert(pn c, pn x) { if (splay(c)==nil) return x; int k=x->key; pn p;
  while (c!=nil) { push(c); p=c; c=(p->key>k?p->l:p->r); }
  p->setc(x,p->key<=k); return splay(x); }
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
void rUpdate(pn c, pn l, pn r, int k, int v) {
  pn u = range(c, l, r); modifyNode(u, k, v); splay(u); }
//%%== Rope operations: split and merge, nil = right end
pn splitBefore(pn x) { if (splay(x)==nil) return nil;
  push(x); if (x->l!=nil) push(x->l);
  pn ret=x->l; x->l=x->l->p=nil; pull(ret); pull(x); return ret; }
pn append(pn l, pn r) { if (splay(l) == nil) return r;
  if (splay(r) == nil) return l; pn x = splay(last(l)); push(x);
  push(r); x->setc(r,1); pull(x->r); pull(x); return x; }
}

pn get_min(pn x) {
  return ST::splay(ST::lower_bound_val(x, 0));
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

  ll ans = 0;
  pn ref = nil;
  ref = ST::insert(ref, new_node(0, INF));
  ref = ST::insert(ref, new_node(-INF, -INF));

  int last_t = 0;
  for(int i=1; i<=n; i++) {
    int t, dir, x;
    cin >> t >> dir >> x;
    int dt = t - last_t;

    pn bot = get_min(ref);
    if(bot->val) {
      int mid = bot->key;
      // move [bot.. right by dt
      ST::rUpdate(ref, ST::prv(bot), nil, dt, 0);
      // add node at mid with slope 0
      ref = ST::insert(ref, new_node(mid, 0));
      // move ..bot) left by dt
      ST::rUpdate(ref, nil, bot, -dt, 0);
    } else {
      ST::rUpdate(ref, bot, nil, dt, 0);
      ST::rUpdate(ref, nil, ST::nxt(bot), -dt, 0);
    }

    bot = get_min(ref); // do it again
    int last_min_left = bot->key;
    int last_min_right = bot->val == 0 ? ST::nxt(bot)->key : bot->key;

    if(dir == 0) { // left
      pn mid = ST::lower_bound(ref, x);
      if(mid->key != x) {
        ref = ST::insert(ref, mid = new_node(x, ST::prv(mid)->val));
      }
      ST::rUpdate(ref, nil, mid, 0, -1);
    } else { // right
      pn mid = ST::lower_bound(ref, x);
      if(mid->key != x) {
        ref = ST::insert(ref, mid = new_node(x, ST::prv(mid)->val));
      }
      ST::rUpdate(ref, ST::prv(mid), nil, 0, 1);
    }

    bot = get_min(ref);
    // go from last_min to bot->key
    if(bot->key < last_min_left) ans += last_min_left - bot->key;
    else if(bot->key > last_min_right) ans += bot->key - last_min_right;
    // cost from shot
    ans += dir == 0 ? max(0, x - bot->key) : max(0, bot->key - x);

    last_t = t;
  }

  cout << ans << nl;

  return 0;
}
