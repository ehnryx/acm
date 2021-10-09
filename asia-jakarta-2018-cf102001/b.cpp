//
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
struct node {
  node *l, *r, *p;
  ll id, key, val, cnt, lazy;
  node(ll i=0, ll k=0, ll v=0);
  inline int dir() { return this == p->l; }
  inline void set_cld(node* c, bool left) { (left?l:r) = c; c->p = this; }
} _null, *null, data[MAXN];
node::node(ll i, ll k, ll v) {
  id=i; key=k; val=v; cnt=1; lazy=0;
  if (!null) { null = &_null; null->cnt = 0; }
  l = r = p = null;
}

namespace SplayTree {
  void update(node* x) { if (x != null) { x->cnt = 1 + x->l->cnt + x->r->cnt; } }
  void modifyNode(node* x, ll v) { if (x != null) { x->val += v; x->lazy += v; } }
  void fix(node* x) { modifyNode(x->l, x->lazy); modifyNode(x->r, x->lazy); x->lazy = 0; }
  inline void rot(node* x) { node *p = x->p; fix(p), fix(x); bool d = x->dir();
    p->set_cld(d ? x->r : x->l, d); p->p->set_cld(x, p->dir()); x->set_cld(p, !d);
    update(p); update(x); }
  void splay(node* x, node* to = null) { if (x == null) return;
    while (x->p != to) { if (x->p->p == to) { rot(x); }
      else (x->dir() == x->p->dir() ? rot(x->p) : rot(x)), rot(x); } }
  int size(node* x) { splay(x); return x->cnt; }

  void insert(node* c, node* x) { splay(c); node *p; if (c == null) { return; }
    ll k = x->key; while (c != null) { p=c, c=(p->key>k ? p->l : p->r); }
    p->set_cld(x,p->key>k); splay(x); }
  node* lb(ll k, node* c) { if (c == null) { return c; } fix(c);
    if (c->key >= k) { node* l = lb(k,c->l); return l==null ? c : l; } return lb(k, c->r); }
  node* lower_bound(ll k, node* root) { splay(root); return lb(k, root); }

  node* begin(node* c) { splay(c);
    while (c!=null && (fix(c),c->l!=null)) { c=c->l; } return c; }
  node* rbegin(node* c) { splay(c);
    while (c!=null && (fix(c),c->r!=null)) { c=c->r; } return c; }
  node* prev(node* x) { splay(x); if (x->l == null) { return null; } x = x->l;
    while (fix(x), x->r != null) { x = x->r; } return x; }
  node* next(node* x) { splay(x); if (x->r == null) { return null; } x = x->r;
    while (fix(x), x->l != null) { x=x->l; } return x; }

  node* rGet(node* root, node* l, node* r) {
    if (l == null) { if (r == null) { return root; } splay(r); return r->l; }
    splay(l); if (r == null) return l->r; splay(r,l); return r->l; }
  ll pQuery(node* x) { splay(x); return x->val; }
  void rUpdate(node* root, node* l, node* r, ll v) { splay(root); 
    node* u=rGet(root,l,r); modifyNode(u,v); splay(u); }

  node* splitBefore(node* x) { if (x == null) { return null; }
    splay(x); fix(x); if (x->l != null) { fix(x->l); } node* root = x->l;
    x->l = x->l->p = null; update(root); update(x); return root; }
  void append(node* root, node* other) { splay(root); splay(other);
    node*& c=other; if (root == null) { c = null; return; }
    if (c == null) { return; } node* x = rbegin(root); splay(x); fix(x); fix(c);
    x->set_cld(c,0); c = null; update(x->r); update(x); }
}


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
  ////cerr << "DETACH " << u << endl;
  node* left = SplayTree::splitBefore(ptr[u]);
  node* right = SplayTree::lower_bound(idx[u]+subsz[u], ptr[u]);
  SplayTree::splitBefore(right);
  SplayTree::append(left, right);
}

void attach(int u) {
  ////cerr << "ATTACH " << u << endl;
  int p = lca[u][0];
  node* left = SplayTree::begin(ptr[p]);
  node* right = SplayTree::lower_bound(idx[u], ptr[p]);
  SplayTree::splitBefore(right);
  SplayTree::append(left, ptr[u]);
  SplayTree::append(ptr[u], right);
}

int rotate(int u, int v) {
  ////cerr << "ROTATE" << endl;
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
  }

  int q, t;
  cin >> q;
  while (q--) {
    cin >> t;
    if (t == 1) {
      int x;
      cin >> x;
      removed[x] = true;
      detach(x);
    } else if (t == 2) {
      int x;
      cin >> x;
      removed[x] = false;
      attach(x);
    } else {
      int x, a;
      cin >> x >> a;
      cout << rotate(x, a) << nl;
    }
    //cerr << "SPLAY TREE: " << nl; for (int j=1; j<=n; j++) {
      //cerr << j << ": sz " << SplayTree::size(ptr[j]) << "  val " << SplayTree::pQuery(ptr[j]);
      //cerr << "  -> "; for (node* x=SplayTree::begin(ptr[j]); x!=null; x=SplayTree::next(x)) {
        //cerr << x->id << " "; }
      //cerr << nl; }
    //cerr << endl;
  }

  int ans = 0;
  for (int i=1; i<=n; i++) {
    int val = SplayTree::pQuery(ptr[i]);
    if (!prty[i]) val = -val;
    //cerr << i << " -> " << val << nl;
    ans += (val % 360 + 360) % 360;
  }
  cout << ans << nl;

  return 0;
}
