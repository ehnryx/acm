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

const int N = 2e5+7;
int val[N], p[N];

struct Item {
  int v, i, j;
  bool operator < (const Item& o) const {
    if(v == o.v) return v < o.v;
    return v < o.v;
  }
};

struct node; using pn = node*;
struct node { pn l, r, p; ll key, val, cnt, lazy, acc; bool rev;
  node(ll k=0, ll v=0);  // pp is for LCT
  inline int dir() { return this == p->r; }
  inline void setc(pn c, bool right) { (right?r:l) = c; c->p = this; }
} dat[N];
pn nil=[](){pn x=dat; x->l=x->r=x->p=x; x->acc=0;
  x->cnt=0; return x;}();
node::node(ll k, ll v): l(nil), r(nil), p(nil),
  key(k), val(v), cnt(1), lazy(0), acc(v), rev(0) {}
int nodeid = 0; template <class... T> pn new_node(T&& ...args) {
  return &(dat[++nodeid] = node(forward<T>(args)...)); }

namespace SplayTree {
//%%== Code for upwards propagating property (eg. count, min)
inline void pull(pn x) { if (x != nil) {
  x->cnt = 1 + x->l->cnt + x->r->cnt;
  x->acc = x->l->acc + x->val + x->r->acc; } }
//%%== Code for lazy propagating property (eg. reverse subtree, add)
void rev(pn x) { if (x != nil) { x->rev ^= 1; swap(x->l, x->r); } }
inline void modifyNode(pn x, ll v) { if (x != nil) {
  /*x->val += v; x->acc += v; x->lazy += v;*/ } }                  //RMQ
//inline void setpp(pn x, pn pp) { if(x!=nil) x->pp = pp; }  // LCT
inline void push(pn x) {
  if (x->rev) { rev(x->l); rev(x->r); x->rev=0; }                  // REV
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
//%%== BST methods (lb, find, insert) (conflicts with other features)
pn lb(pn c, ll k) { if (c == nil) return c; // c MUST BE THE ROOT
  push(c); if (c->key>=k) { pn l=lb(c->l,k); return l==nil?c:l; }
  return lb(c->r,k); }
pn lowerBound(pn ref, ll k) { return lb(splay(ref), k); }
pn find(pn c, ll k) { c=lb(splay(c),k); return c->key!=k?nil:splay(c); }
pn insert(pn c, pn x) { if (splay(c)==nil) return x; ll k=x->key; pn p;
  while (c!=nil) { push(c); p=c; c=(p->key>k?p->l:p->r); }
  p->setc(x,p->key<=k); return splay(x); }
//%%== Utility code (rank, nth order statistic; requires cnt maintained)
int idx(pn x) { return splay(x)->l->cnt; } // rank; for sz, remove '->l'
int size(pn x) { return splay(x)->cnt; }
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
ll pQuery(pn x) { return splay(x)->val; }
ll rQuery(pn c, pn l, pn r) { return range(c, l, r)->acc; }
void pUpdate(pn x, ll v) { splay(x)->val += v; pull(x); }          //RMQ
void rUpdate(pn c, pn l, pn r, ll v) {
  pn u = range(c, l, r); modifyNode(u, v); splay(u); }
//%%== Rope operations: split and merge, nil = right end
pn splitBefore(pn x) { if (splay(x)==nil) return nil;
  push(x); if (x->l!=nil) push(x->l);
  pn ret=x->l; x->l=x->l->p=nil; pull(ret); pull(x); return ret; }
pn append(pn l, pn r) { if (splay(l) == nil) return r;
  if (splay(r) == nil) return l; pn x = splay(last(l)); push(x);
  push(r); x->setc(r,1); pull(x->r); pull(x); return x; }
}

pn nds[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, k;
  cin >> n >> k;
  unordered_map<string,int> idx;
  for(int i=1; i<=n; i++) {
    string s;
    cin >> s >> val[i];
    if(isdigit(s.back())) {
      if(s.back() == '1') {
        s.pop_back();
        idx[s] = i;
      } else {
        s.pop_back();
        p[i] = idx[s];
      }
    }
  }

  for(int i=1; i<=n; i++) {
    nds[i] = new_node(i, val[i]);
  }

  unordered_set<int> skip;
  for(int i=1; i<=n; i++) {
    if(p[i] && val[i] < val[p[i]]) {
      skip.insert(p[i]);
    }
  }
  vector<Item> pairs, nodes;
  for(int i=1; i<=n; i++) {
    if(skip.count(i)) continue;
    if(p[i] && val[i] < val[p[i]]) {
      pairs.push_back({val[i] + val[p[i]], i, p[i]});
      nodes.push_back({val[p[i]], p[i]});
    } else {
      nodes.push_back({val[i], i});
    }
  }
  sort(pairs.begin(), pairs.end());
  sort(nodes.begin(), nodes.end());

  pn root = nil;
  for(auto [v,i,_] : nodes) {
    root = SplayTree::append(root, nds[i]);
  }

  ll ans = INFLL;
  if(k <= SplayTree::size(root)) {
    pn r = SplayTree::nth(root, k);
    ans = min(ans, SplayTree::rQuery(root, nil, r));
  }
  ll tot = 0;
  for(auto [v,i,j] : pairs) {
    tot += v;
    k -= 2;
    root = SplayTree::del(nds[j]);
    if(k < 0) break;
    if (k <= SplayTree::size(root)) {
      pn r = SplayTree::nth(root, k);
      ans = min(ans, tot + SplayTree::rQuery(root, nil, r));
    }
  }
  cout << ans << nl;

  return 0;
}
