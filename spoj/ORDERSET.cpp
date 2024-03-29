#include <bits/stdc++.h>

using namespace std;
typedef int ll;
const int MAXN = 200005;
const int INF = 0x3f3f3f3f;

// this version is to benchmark splay tree with all features enabled

/* BEGIN code archive splay tree with REV and RMQ */
struct node { node *l, *r, *p; ll id, key, val, cnt, lazy, acc; bool rev;
  node(ll i=0, ll k=0, ll v=0);
  inline int dir() { return this == p->l; }
  inline void set_cld(node* c, bool left) { (left?l:r) = c; c->p = this; }
} _null, *null, data[MAXN];
node::node(ll i, ll k, ll v) { id=i; key=k; val=v; cnt=1; lazy=0; acc=v; rev=0;
  if (!null) { null=&_null; null->cnt=0; /*null->acc=INF;*/ } l=r=p=null;} //RMQ

//%%== Code for upwards propagating property (eg. count, min)
void update(node* x) { if (x != null) { x->cnt = 1 + x->l->cnt + x->r->cnt;
  /*x->acc = min(x->l->acc, min(x->val, x->r->acc));*/ } }                 //RMQ
//%%== Code for downward lazy propagating property (eg. reverse subtree, add)
void rev(node* x) { if (x != null) { x->rev ^= 1; swap(x->l, x->r); } }
void modifyNode(node* x, ll v) { if (x != null) {
  /*x->val += v; x->acc += v; x->lazy += v;*/ } }                          //RMQ
void fix(node* x) { /*if (x->rev) { rev(x->l); rev(x->r); x->rev=0; }*/    //REV
  /*modifyNode(x->l, x->lazy); modifyNode(x->r, x->lazy); x->lazy=0;*/ }   //RMQ
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
int Srank(node* x) { return splay(x)->l->cnt; }
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
void insertBefore(node* c, node* at, node* x) { // to insert "last", use at=null
  if (at==null) { if(splay(c)!=null) rbegin(c)->set_cld(x,0); } else {
  node* p=prv(at);if(p==null)at->set_cld(x,1); else p->set_cld(x,0);} splay(x);}
//%%== Range query and update operations by iterator, range is EXCLUSIVE!
node* rGet(node* ref, node* l, node* r) {
  if(l==null) { if(r==null) { return splay(ref); } splay(r); return r->l; }
  splay(l); if (r==null) { return l->r; } splay(r, l); return r->l; }
ll pQuery(node* x) { splay(x); return x->val; }
ll rQuery(node* c, node* l, node* r) { return rGet(c, l, r)->acc; }
void pUpdate(node* x, ll v) { splay(x); x->val += v; update(x); }          //RMQ
void rUpdate(node* c, node* l, node* r, ll v) {
  node* u = rGet(c, l, r); modifyNode(u, v); splay(u); }
//%%== Rope operations: split and merge, null = right end
node* splitBefore(node* x) { if (splay(x) == null) return null;
  fix(x); if (x->l != null) fix(x->l); node* ret = x->l; x->l = x->l->p = null;
  update(ret); update(x); return ret; }
void append(node* ref, node* other) { splay(ref); splay(other);
  if (ref == null || other == null) return; node* x = splay(rbegin(ref));
  fix(x); fix(other); x->set_cld(other,0); update(x->r); update(x); }
/* END code archive splay tree */

#define nl '\n'
int main() {
    int nq; scanf("%d", &nq);
    int nn = 0;
    node* root = null;
    while (nq--) {
        char c; int x; scanf(" %c %d", &c, &x);
        if (c == 'I') {
            if (find(root, x) == null) {
                root = insert(root, new (&data[nn++]) node(0, x, 0));
            }
        } else if (c == 'D') {
            node * cur = find(root, x);
            if (cur != null) {
                root = del(cur);
            }
        } else if (c == 'K') {
            if (x >= 1 && x <= splay(root)->cnt) {
                node * cur = nth(root, x-1);
                printf("%d\n", splay(cur)->key);
            } else {
                printf("invalid\n");
            }
        } else if (c == 'C') {
            node* cur = lower_bound(root, x);
            if (cur == null) {
                //cerr << "NULL" << nl;
                printf("%d\n", size(root));
            } else {
                //cerr << "cur->key" << " " << cur->key << nl;
                printf("%d\n", Srank(cur));
            }
        }
        //cerr << "root: " << root->key << "  ";
        //if (root->p == null) cerr << "child: " << root->l->key << " " << root->r->key << nl;
        //else cerr << "parent: " << root->p->key << nl;
        //cerr << "SPLAY TREE" << nl; for (node* x=begin(root); x!=null; x=nxt(x)) {
          //cerr << x->key << " "; }
        //cerr << nl;
    }
    //assert(null->l == null && null->r == null && null->p == null);
    return 0;
}
