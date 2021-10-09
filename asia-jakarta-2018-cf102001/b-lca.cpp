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

const int MAXN = 1<<17;

struct node { node *l, *r, *p; ll id, key, val, cnt, lazy, acc; bool rev;
  node(ll i=0, ll k=0, ll v=0);
  inline int dir() { return this == p->l; }
  inline void set_cld(node* c, bool left) { (left?l:r) = c; c->p = this; }
} _null, *null, data[MAXN];
node::node(ll i, ll k, ll v) { id=i; key=k; val=v; cnt=1; lazy=0; acc=v; rev=0;
  if (!null) { null=&_null; null->cnt=0; /*null->acc=INF;*/ } l=r=p=null;} //RMQ

namespace SplayTree {
//%%== Code for upwards propagating property (eg. count, min)
void update(node* x) { if (x != null) { x->cnt = 1 + x->l->cnt + x->r->cnt;
  /*x->acc = min(x->l->acc, min(x->val, x->r->acc));*/ } }                 //RMQ
//%%== Code for downward lazy propagating property (eg. reverse subtree, add)
void rev(node* x) { if (x != null) { x->rev ^= 1; swap(x->l, x->r); } }
void modifyNode(node* x, ll v) { if (x != null) {
  x->val += v; x->acc += v; x->lazy += v; } }                          //RMQ
void fix(node* x) { /*if (x->rev) { rev(x->l); rev(x->r); x->rev=0; }*/    //REV
  modifyNode(x->l, x->lazy); modifyNode(x->r, x->lazy); x->lazy=0; }   //RMQ
//%%== call fixDownTo() before using node if an ancestor may have un-pushed lazy
void fixDownTo(node* c) { if (c->p != null) fixDownTo(c->p); fix(c); }
//%%== Core splay tree code (rotate, splay, delete)
inline void rot(node* x) { node *p = x->p; fix(p), fix(x); bool d = x->dir();
  p->set_cld(d ? x->r : x->l, d); p->p->set_cld(x, p->dir()); x->set_cld(p, !d);
  update(p); update(x); }
// splays node x until it is a child of node to
node* splay(node* x, node* to=null) { if (x==null) return x; while(x->p != to)
  if(x->p->p==to) rot(x); else { x->dir()==x->p->dir() ? rot(x->p) : rot(x);
  rot(x); } return x; }
node* del(node* y) { node* x=splay(y)->r; if (x==null) x=y->l; else {
  while (fix(x), x->l != null) x = x->l; splay(x,y)->set_cld(y->l,1); }
  x->p=null; update(x); return x; }
//%%== BST methods (lb, find, insert) (conflicts with other features, see above)
node* lb(node* c, ll k) { if (c == null) return c; fix(c); // c MUST BE THE ROOT
  if(c->key>=k) { node* l=lb(c->l,k); return l==null?c:l; } return lb(c->r,k); }
node* lower_bound(node* ref, ll k) { return lb(splay(ref), k); }
node* find(node* c, ll k) { c=lb(splay(c),k); return c->key!=k?null:splay(c); }
node* insert(node* c, node* x) { if (splay(c) == null) return x;
  ll k=x->key; node* p; while(c!=null) { fix(c); p=c; c=(p->key>k?p->l:p->r); }
  p->set_cld(x,p->key>k); return splay(x); }
//%%== Utility code (rank, nth order statistic) (requires count maintained)
int size(node* x) { return splay(x)->cnt; }
int rank(node* x) { return splay(x)->l->cnt; }
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
node* rGet(node* c, node* l, node* r){ if(l==null){ if(r==null) return splay(c);
  return splay(r)->l; } splay(l); if(r==null)return l->r; return splay(r,l)->l;}
ll pQuery(node* x) { return splay(x)->val; }
ll rQuery(node* c, node* l, node* r) { return rGet(c, l, r)->acc; }
void pUpdate(node* x, ll v) { splay(x)->val += v; update(x); }             //RMQ
void rUpdate(node* c, node* l, node* r, ll v) {
  node* u = rGet(c, l, r); modifyNode(u, v); splay(u); }
//%%== Rope operations: split and merge, null = right end
node* splitBefore(node* x) { if (splay(x) == null) return null;
  fix(x); if (x->l != null) fix(x->l); node* ret = x->l; x->l = x->l->p = null;
  update(ret); update(x); return ret; }
node* append(node* ref, node* other) { if (splay(ref)==null) return other;
  if (splay(other)==null) return ref; node* x=splay(rbegin(ref)); fix(x);
  fix(other); x->set_cld(other,0); update(x->r); update(x); return x; } }


const int N = 1<<17;
const int L = 17;
vector<int> adj[N];
node* ptr[N];
int prty[N], idx[N], subsz[N], depth[N];
int lca[N][L];
bool removed[N];

void precmp(int u, int p, int id, int val) {
  depth[u] = depth[p]+1;
  lca[u][0] = p;
  for (int j=1; j<L; j++) {
    lca[u][j] = lca[lca[u][j-1]][j-1];
  }
  prty[u] = val;
  idx[u] = id++;
  subsz[u] = 1;
  for (int v : adj[u]) {
    if (v != p) {
      precmp(v, u, id, val^1);
      subsz[u] += subsz[v];
      id += subsz[v];
    }
  }
}

int jump(int u, int len) {
  for (int i=0; i<L; i++) {
    if (len&1<<i) {
      u = lca[u][i];
    }
  }
  return u;
}

void detach(int u) {
  //////cerr << "DETACH " << u << endl;
  node* left = SplayTree::splitBefore(ptr[u]);
  node* right = SplayTree::lower_bound(ptr[u], idx[u]+subsz[u]);
  SplayTree::splitBefore(right);
  SplayTree::append(left, right);
}

void attach(int u) {
  //////cerr << "ATTACH " << u << endl;
  int p = lca[u][0];
  node* left = SplayTree::begin(ptr[p]);
  node* right = SplayTree::lower_bound(ptr[p], idx[u]);
  SplayTree::splitBefore(right);
  SplayTree::append(left, ptr[u]);
  SplayTree::append(ptr[u], right);
}

int rotate(int u, int v) {
  //////cerr << "ROTATE" << endl;
  node* root = SplayTree::begin(ptr[u]);
  if (removed[root->id]) {
    int anc = jump(u, depth[u]-depth[root->id]-1);
    detach(anc);
    SplayTree::rUpdate(ptr[anc], null, null, prty[u] ? v : -v);
    int ret = v * SplayTree::size(ptr[anc]);
    attach(anc);
    return ret;
  } else {
    SplayTree::rUpdate(root, null, null, prty[u] ? v : -v);
    return v * SplayTree::size(root);
  }
}

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

  for (int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  precmp(1, 0, 1, 0);

  ptr[0] = null;
  for (int i=1; i<=n; i++) {
    ptr[i] = new (&data[i]) node(i, idx[i], 0);
    if (i>1) SplayTree::insert(ptr[1], ptr[i]);
    //cerr << "INITIAL SPLAY TREE: " << endl; for (int j=1; j<=i; j++) {
      //cerr << j << ": sz " << SplayTree::size(ptr[j]) << "  val " << SplayTree::pQuery(ptr[j]);
      //cerr << "  -> "; for (node* x=SplayTree::begin(ptr[j]); x!=null; x=SplayTree::nxt(x)) {
        //cerr << x->id << " "; }
      //cerr << endl; }
    //cerr << endl;
  }

  int q, t;
  cin >> q;
  while (q--) {
    cin >> t;
    if (t == 1) {
      int x;
      cin >> x;
      //cerr << "QUERY " << t << " " << x << endl;
      removed[x] = true;
      detach(x);
    } else if (t == 2) {
      int x;
      cin >> x;
      //cerr << "QUERY " << t << " " << x << endl;
      removed[x] = false;
      attach(x);
    } else {
      int x, a;
      cin >> x >> a;
      //cerr << "QUERY " << t << " " << x << " " << a << endl;
      cout << rotate(x, a) << nl;
    }
    //cerr << "SPLAY TREE: " << endl; for (int j=1; j<=n; j++) {
      //cerr << j << ": sz " << SplayTree::size(ptr[j]) << "  val " << SplayTree::pQuery(ptr[j]);
      //cerr << "  -> "; for (node* x=SplayTree::begin(ptr[j]); x!=null; x=SplayTree::nxt(x)) {
        //cerr << x->id << " "; }
      //cerr << endl; }
    //cerr << endl;
  }

  int ans = 0;
  for (int i=1; i<=n; i++) {
    int val = SplayTree::pQuery(ptr[i]);
    if (!prty[i]) val = -val;
    ////cerr << i << " -> " << val << nl;
    ans += (val % 360 + 360) % 360;
  }
  cout << ans << nl;

  return 0;
}
