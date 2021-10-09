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

const int N = 3e5+7;
struct node; using pn = node*;
struct node { pn l,r,p,pp; int val, cnt, lazy; bool rev;
  node();
  inline int dir() { return this == p->r; }
  inline void setc(pn c, bool right) { (right?r:l)=c; c->p=this; }
} dat[N];
pn nil=[]() { pn x=dat; x->l = x->r = x->p = x;
  x->cnt = 0; x->val = 0; return x; } () ;
node::node(): l(nil), r(nil), p(nil), pp(nil),
  val(0), cnt(1), lazy(0), rev(0) {}
int nodeid = 0; template <class... T> pn new_node(T&& ...args) {
  return &(dat[++nodeid] = node(forward<T>(args)...)); }

namespace SplayTree {
  inline void pull(pn x) { if(x!=nil) {
    x->cnt = 1 + x->l->cnt + x->r->cnt; } }
  void rev(pn x) { if(x!=nil) { x->rev ^= 1; swap(x->l, x->r); } }
  inline void modifyNode(pn x, int v) { if(x!=nil) {
    x->val += v; x->lazy += v; } }
  inline void setpp(pn x, pn pp) { if(x!=nil) x->pp = pp; }
  inline void push(pn x) {
    if(x->rev) { rev(x->l); rev(x->r); x->rev = 0; }
    setpp(x->l, x->pp); setpp(x->r, x->pp);
    modifyNode(x->l, x->lazy); modifyNode(x->r, x->lazy); x->lazy=0;
  }
  void rot(pn x) { pn p = x->p; push(p); push(x); bool d=x->dir();
    p->setc(d ? x->l : x->r, d);
    p->p->setc(x, p->dir()); x->setc(p, !d);
    pull(p); pull(x); }
  pn splay(pn x, pn to=nil) { if(x!=nil) { while(x->p!=to) {
    if(x->p->p!=to) rot(x->dir()==x->p->dir() ? x->p : x);
    rot(x); } } return x; }
  pn first(pn c) { if(splay(c) != nil) {
    while(push(c),c->l!=nil) c=c->l; } return splay(c); }

  pn range(pn c, pn l, pn r) { if(l==nil) {
    if(r==nil) { return splay(c); } return splay(r)->l; }
    if(l==r) { return nil; } splay(l);
    if(r==nil) { return l->r; } return splay(r,l)->l; }
  void rUpdate(pn c, pn l, pn r, int v) {
    pn u = range(c,l,r); modifyNode(u,v); splay(u); }
  int pQuery(pn x) { return splay(x)->val; }

  struct LinkCutTree {
    vector<pn> nds;
    LinkCutTree(int n=0) { init(n); }
    void init(int n) { nds.resize(n, nil);
      for(int i=0; i<n; i++) nds[i] = new_node(); }
    pn splitAfter(pn x) { push(x); push(x->r); pn bot=x->r;
      x->r = x->r->p = nil; pull(bot); pull(x); return bot; }
    void join(pn l, pn r) { pn x = splay(first(r)); x->pp = l->pp;
      push(x); push(splay(l)); x->setc(l,0); pull(x->l); pull(x); }
    pn access(pn x) { if(splay(x)->r!=nil) { splitAfter(x)->pp=x; }
      for(pn w=x; pull(w), splay(w=x->pp)!=nil; splay(x)) {
        if(w->r != nil) { splitAfter(w)->pp=w; }
        join(w, x); } return x; }
    void link(int x, int y) {
      join(access(nds[y]), reroot(nds[x]));
    }
    void cut(int x, int y) {
      reroot(nds[y]); access(nds[x]); splitAfter(nds[y]);
    }
    void reroot(int x) { reroot(nds[x]); }
    pn reroot(pn x) { rev(access(x)); push(x); return x; }

    void insert_path(int x, int y, int v) {
      assert(nds[x] != nil);
      reroot(nds[x]); access(nds[y]); rUpdate(nds[x],nil,nil,v); }
    int query_node(int x) { return pQuery(nds[x]); }
  };
}

char c[N];
int fail[N];
int failj = 0;
void update(int i) {
  while(failj>0 && c[failj+1] != c[i]) {
    failj = fail[failj];
  }
  if(failj+1 < i && c[failj+1] == c[i]) {
    fail[i] = ++failj;
  } else {
    assert(failj == 0);
    fail[i] = failj;
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  SplayTree::LinkCutTree lct(n+1);
  int id = 0;
  int last = 0;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    if(s == "add") {
      cin >> c[++id];
      c[id] = (c[id]-'a' + last) % 26 + 'a';
      //cerr<<"insert "<<c[id]<<nl;
      update(id);
      lct.link(id, fail[id]);
      //cerr<<"lct link "<<id<<" "<<fail[id]<<nl;
      lct.insert_path(id, 0, 1);
      //cerr<<"insert path "<<0<<" "<<id<<nl;
    } else {
      int x;
      cin >> x;
      x = (x-1+last) % id + 1;
      //cerr<<"query "<<x<<nl;
      last = lct.query_node(x);
      cout << last << nl;
    }
  }

  return 0;
}
