//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<17;

struct node; using pn = node*;
struct node { pn l, r, p, pp; int key, val, cnt, lazy, acc; bool rev;
  node(int k=0, int v=0);  // pp is for LCT
  inline int dir() { return this == p->r; }
  inline void setc(pn c, bool right) { (right?r:l) = c; c->p = this; }
} dat[N]; // nil = dat[0]
pn nil=[](){pn x=dat; x->l=x->r=x->p=x; /*x->acc=INF;*/ // RMQ
  x->cnt=0; return x;}();
node::node(int k, int v): l(nil), r(nil), p(nil), pp(nil),
  key(k), val(v), cnt(1), lazy(0), acc(v), rev(0) {}
int nodeid = 0; template <class... T> pn new_node(T&& ...args) {
  return &(dat[++nodeid] = node(forward<T>(args)...)); }

namespace SplayTree {
//%%== Code for upwards propagating property (eg. count, min)
inline void pull(pn x) { if (x != nil) {
  x->cnt = 1 + x->l->cnt + x->r->cnt; } }
//%%== Code for lazy propagating property (eg. reverse subtree, add)
void rev(pn x) { if (x != nil) { x->rev ^= 1; swap(x->l, x->r); } }
inline void setpp(pn x, pn pp) { if(x!=nil) x->pp = pp; }  // LCT
inline void push(pn x) {
  if (x->rev) { rev(x->l); rev(x->r); x->rev=0; }                  //REV
  setpp(x->l, x->pp); setpp(x->r, x->pp);  // LCT
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
//%%== Iterator-based access, returns nil when iterator exhausted
pn first(pn c) { if (splay(c) != nil)
  while (push(c), c->l != nil) c=c->l; return splay(c); }

struct LinkCutTree { vector<pn> nds;
  LinkCutTree(int n=0) { init(n); }
  void init(int n) { nds.resize(n, nil);
    for(int i=0;i<n;i++) nds[i] = new_node(i); }
  pn splitAfter(pn x) { push(x); push(x->r); pn bot = x->r;
    x->r = x->r->p = nil; pull(bot); pull(x); return bot; }
  void join(pn l, pn r) { pn x = splay(first(r)); x->pp = l->pp;
    push(x); push(splay(l)); x->setc(l,0); pull(x->l); pull(x); }
  pn access(pn x) { if(splay(x)->r != nil) { splitAfter(x)->pp = x; }
    for(pn w=x; pull(w), splay(w=x->pp)!=nil; splay(x)) {
      if(w->r!=nil) { splitAfter(w)->pp=w; } join(w,x); } return x; }
  void link(int x, int y) { join(access(nds[y]), reroot(nds[x])); }
  void cut(int x, int y) { reroot(nds[x]); access(nds[y]);
    splitAfter(splay(nds[x]))->pp = nil; }
  void reroot(int x) { reroot(nds[x]); }
  pn reroot(pn x) { rev(access(x)); push(x); return x; }
  int findroot(int x) { return findroot(nds[x])->key; }
  pn findroot(pn x) { return first(access(x)); }
  int depth(int x) { return depth(nds[x]); }
  int depth(pn x) { return splay(access(x))->l->cnt; }
}; }

SplayTree::LinkCutTree lct;

int ans[N];
vector<pair<int,int>> add[2*N];

void add_range(int l, int r, pair<int,int> v, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return;
  if(l<=s && e<=r) {
    add[i].push_back(v);
    return;
  }
  int m = (s+e) / 2;
  add_range(l, r, v, 2*i, s, m);
  add_range(l, r, v, 2*i+1, m+1, e);
}

bool link(int a, int b, vector<pair<int,int>>& memo) {
  lct.reroot(a);
  if(lct.findroot(b) != a) {
    lct.link(a, b);
    memo.emplace_back(a, b);
    return true;
  } else {
    return lct.depth(b) % 2;
  }
}

void unlink(int a, int b) {
  lct.cut(a, b);
}

void solve(int l, int r, bool cur=true, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return;
  vector<pair<int,int>> memo;
  for(auto [a, b] : add[i]) {
    cur &= link(a, b, memo);
  }

  if(s == e) {
    ans[s] = cur;
  } else {
    int m = (s+e) / 2;
    solve(l, r, cur, 2*i, s, m);
    solve(l, r, cur, 2*i+1, m+1, e);
  }

  for(auto [a, b] : memo) {
    unlink(a, b);
  }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  lct.init(n+1);

  map<pair<int,int>,vector<int>> edges;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    edges[make_pair(a, b)].push_back(i);
  }

  for(auto& [e, it] : edges) {
    sort(it.begin(), it.end());
    int pre = -1;
    for(int i : it) {
      if(pre == -1) {
        pre = i;
      } else {
        add_range(pre, i-1, e);
        pre = -1;
      }
    }
    if(pre != -1) {
      add_range(pre, m-1, e);
    }
  }
  solve(0, m-1);

  for(int i=0; i<m; i++) {
    cout << (ans[i] ? "YES" : "NO") << nl;
  }

  return 0;
}
