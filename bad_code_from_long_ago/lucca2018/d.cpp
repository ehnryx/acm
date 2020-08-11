#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
    os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
    for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
    os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
    os << "{ ";
    for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
    os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct node { node *l, *r, *p; ll id, key, val, cnt, lazy, acc; bool rev;
  node(ll i=0, ll k=0, ll v=0);
  inline int dir() { return this == p->l; }
  inline void set_cld(node* c, bool left) { (left?l:r) = c; c->p = this; }
} _null, *null; //, data[MAXN];

node::node(ll i, ll k, ll v) { id=i; key=k; val=v; cnt=1; lazy=0; acc=v; rev=0;
  if (!null) { null=&_null; null->cnt=0; null->acc=0; } l=r=p=null;} //RMQ

struct SplayTree { node *root; SplayTree() { root = null; }
//%%== Code for upwards propagating property (eg. count, min)
void update(node* x) { if (x != null) { x->cnt = 1 + x->l->cnt + x->r->cnt;
    x->acc = max(x->val, max(x->l->acc, x->r->acc)); // RMQ
}}

//%%== Code for downward lazy propagating property (eg. reverse subtree, add)
void rev(node* x) { if (x != null) { x->rev ^= 1; swap(x->l, x->r); } }
void modifyNode(node* x, ll v) { if (x != null) {
  /*x->val += v; x->acc += v; x->lazy += v;*/ } }                          //RMQ
void fix(node* x) { /*if (x->rev) { rev(x->l); rev(x->r); x->rev=0; }*/    //REV
  /*modifyNode(x->l, x->lazy); modifyNode(x->r, x->lazy); x->lazy=0;*/ }   //RMQ

//%%== Core splay tree code (rotate, splay, delete)
inline void rot(node* x) { node *p = x->p; fix(p), fix(x); bool d = x->dir();
  p->set_cld(d ? x->r : x->l, d); p->p->set_cld(x, p->dir()); x->set_cld(p, !d);
  update(p); update(x); if (p == root) root = x; }
// splays node x until it is a child of node to
void splay(node* x, node* to = null) { if (x == null) return; while(x->p != to)
  if(x->p->p==to) rot(x); else (x->dir()==x->p->dir()?rot(x->p):rot(x)),rot(x);}
void del(node* x){ splay(x); x = x->r; while (fix(x), x->l != null) x = x->l;
  if (x==null) x = root->l; else { splay(x, root); x->set_cld(root->l, 1); }
  x->p = null; update(root = x); }
//%%== BST methods (lb, find, insert) (conflicts with other features, see above)
node* lb(ll k, node* c) { if (c == null) return c; fix(c);
  if(c->key >= k){ node* l=lb(k,c->l); return l==null?c:l; } return lb(k,c->r);}
node* lb(ll k) { return lb(k, root); }
node* find(ll k) { node* c=lb(k); if (c->key!=k) c=null; splay(c); return c; }
void insert(node* x) { node *c=root,*p; if(c==null){root=x;return;} ll k=x->key;
  while(c!=null) p=c, c=(p->key>k?p->l:p->r); p->set_cld(x,p->key>k); splay(x);}
//%%== Utility code (rank, nth order statistic) (requires count maintained)
int rank(node* x) { if (x == NULL) return -1; splay(x); return x->l->cnt; }
node* nth(int n) { node* c = root; while(c != null) { fix(c); int l=c->l->cnt;
  if (n==l) break; if (n < l) c = c->l; else n = n-l-1, c = c->r; } return c; }
//%%== Iterator-based access, returns null when iterator exhausted
node*  begin(){node *c=root;while(c!=null&&(fix(c),c->l!=null))c=c->l;return c;}
node* rbegin(){node *c=root;while(c!=null&&(fix(c),c->r!=null))c=c->r;return c;}
node* prv(node* x) { splay(x); if (x->l == null) return null; x = x->l;
  while (fix(x), x->r != null) x=x->r; return x; }
node* nxt(node* x) { splay(x); if (x->r == null) return null; x = x->r;
  while (fix(x), x->l != null) x=x->l; return x; }
//%%== Iterator-based insert, does NOT work with BST code unless key sorted
void insertBefore(node* at, node* x) { // to insert "last", use at = null
  if(at==null) { if(root==null) root=x; else rbegin()->set_cld(x,0); } else {
  node* p=prv(at);if(p==null)at->set_cld(x,1); else p->set_cld(x,0);} splay(x);}
//%%== Range query and update operations by iterator, range is EXCLUSIVE!
node* rGet(node* l, node* r) { // splay (l, r) into 1 subtree & return its root
  if(l==null) { if(r==null) return root; splay(r); return r->l; }
  splay(l); if (r==null) return l->r; splay(r, l); return r->l; }
ll pQuery(node* x) { splay(x); return x->val; }
ll rQuery(node* l, node* r) { return rGet(l, r)->acc; }
void pUpdate(node* x, ll v) { splay(x); x->val += v; update(x); }          //RMQ
void rUpdate(node* l,node* r,ll v){node* u=rGet(l,r);modifyNode(u,v);splay(u);}
//%%== Rope operations: split and merge, null = right end
SplayTree splitBefore(node* x) { SplayTree ret; if (x == null) return ret;
  splay(x); fix(x); if (x->l != null) fix(x->l); ret.root=x; root=x->l;
  x->l->p=null; x->l=null; update(root); update(ret.root); return ret; }
void append(SplayTree &other) { // 'other' is destroyed after merge
  node*& c=other.root; if (root == null) { root = c; c = null; return; }
  if (c == null) return; node* x = rbegin(); splay(x); fix(x); fix(c);
  x->set_cld(c, 0); c = null; update(x->r); update(x); } 

    node* rmax(node* x, int lb) {
        if (x == null || x->acc <= lb) return null;
        node* ans = rmax(x->r, lb);
        if (ans != null) return ans;
        if (x->val > lb) return x;
        else return rmax(x->l, lb);
    }

    node* rmq(node* x, int lb) {
        splay(x); return rmax(x->l, lb + x->val);
    }
};

SplayTree mess;

const int N = 1<<21;
int height[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    node* x = null;

    int n;
    cin >> n;

    int ppl = n;
    int t, a, b;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        x = new node(0, i, a);
        mess.insertBefore(null, x);
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        cin >> t >> a >> b;

        if (t == 0) {
            ppl++;
            x = new node(1, i, b);
            mess.insertBefore(mess.nth(a), x);
        }

        else {
            x = mess.rmq(mess.nth(a-1), b);
            cout << ((x == null) ? 0 : 1 + mess.rank(x)) << nl;
        }
    }

    return 0;
}
