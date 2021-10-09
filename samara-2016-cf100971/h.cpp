#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct node { node *l, *r, *p; ll key, cnt;
  node(ll k=0);
  inline int dir() { return this == p->l; }
  inline void set_cld(node* c, bool left) { (left?l:r) = c; c->p = this; }
} _null, *null;
node::node(ll k) { key=k; cnt=1;
  if (!null) { null=&_null; null->cnt=0; /*null->acc=INF;*/ } l=r=p=null;} //RMQ
namespace SplayTree {
//%%== Code for upwards propagating property (eg. count, min)
void update(node* x) { if (x != null) { x->cnt = 1 + x->l->cnt + x->r->cnt;
  /*x->acc = min(x->l->acc, min(x->val, x->r->acc));*/ } }                 //RMQ
//%%== Core splay tree code (rotate, splay, delete)
inline void rot(node* x) { node *p = x->p; bool d = x->dir();
  p->set_cld(d ? x->r : x->l, d); p->p->set_cld(x, p->dir()); x->set_cld(p, !d);
  update(p); update(x); }
// splays node x until it is a child of node to
node* splay(node* x, node* to=null){ if(x!=null){ while(x->p!=to)if(x->p->p==to)
  rot(x); else { x->dir()==x->p->dir()?rot(x->p):rot(x); rot(x); }} return x; }
node* del(node* y) { node* x=splay(y)->r; if (x==null) x=y->l; else {
  while (x->l != null) x = x->l; splay(x,y)->set_cld(y->l,1); }
  x->p=null; update(x); return x; }
//%%== BST methods (lb, find, insert) (conflicts with other features, see above)
node* insert(node* c, node* x) { if (splay(c) == null) return x;
  ll k=x->key; node* p; while(c!=null) { p=c; c=(p->key>k?p->l:p->r); }
  p->set_cld(x,p->key>k); return splay(x); }
//%%== Utility code (rank, nth order statistic) (requires count maintained)
node* nth(node* c, int n) { splay(c); while (c!=null) { int l=c->l->cnt;
  if (n==l) break; if (n < l) c = c->l; else n = n-l-1, c = c->r; } return splay(c); }
}

struct Point {
  int i, x, t;
  bool operator < (const Point& o) const {
    if (x != o.x) return x < o.x;
    else return t > o.t;
  }
};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n;
  cin >> n;

  vector<Point> p;
  for (int i=1; i<=n; i++) {
    int l, r;
    cin >> l >> r;
    p.push_back({i,l,1});
    p.push_back({i,r,-1});
    p.push_back({i,i,0});
  }
  sort(p.begin(), p.end());

  node* cur = null;
  node ptr[n+1];
  for (const Point& it : p) {
    if (it.t == 1) {
      ptr[it.i] = node(it.i);
      cur = SplayTree::insert(cur, &ptr[it.i]);
    } else if (it.t == -1) {
      cur = SplayTree::del(&ptr[it.i]);
    } else { // it.t == 0
      node* nth = SplayTree::nth(cur,it.x-1);
      if (nth == null) {
        cout << -1 << " ";
      } else {
        cout << nth->key << " ";
      }
    }
  }
  cout << nl;

  return 0;
}
