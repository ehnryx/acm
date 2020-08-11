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

////////////////////////////////////////////////////////////////////////////////
// Link-cut tree: O(lg n) for all ops, TESTED (DYNALCA, DYNACON1, and more)
////////////////////////////////////////////////////////////////////////////////
// link(p, q) - makes the *root* p a child of the node q. if p is not a root,
//              makeroot will be called and lca(p, q) will be changed.
// cut(p) - deletes the edge connecting p to its parent
// cut(p, q) - delete the edge connecting p to q (or on the path from p to q)
// pathAggregate(p, q) - returns the sum of weights on the path from p to q.
//                       this operation can be min, adding a constant, etc.
// pathUpdate(p, q) - increase value of all nodes between x and y inc. by c.
// lca(p, q) - returns lca of nodes p and q.
// findroot(p) - returns the root of node p's tree
// makeroot(p) - makes p the root of its tree
struct LinkCutTree { vector<int> l,r,p,pp,val,sum,carry,size,flip; int null;
  void init(int n) {
    vector<int>* v[] = {&l, &r, &p, &pp, &size, &val, &sum, &carry, &flip};
    int ival[] = {null=n, null, null, null, 1, 0, 0, 0, 0};
    for (int i = 0; i < 9; i++) { v[i]->clear(); v[i]->resize(n+1, ival[i]); }
    size[null] = 0; }
  inline int access(int x) {
    if(r[splay(x)] != null) r[pp[r[x]] = x] = p[r[x]] = null;
    for(int w=x; update(w)>=0 && splay(w=pp[x]) != null; splay(r[p[x]=w]=x))
      if(r[w] != null) p[r[pp[r[w]]=w]] = null;
    return x; }
  void makeroot(int x) { access(x); flip[x] ^= 1; push(x); }
  int findroot(int x) {
    for(access(x); l[x] != null; x = l[x]) {}
    return access(x); }
  int pathAggregate(int x) { return sum[access(x)]; }
  int pathAggregate(int x, int y) { makeroot(x); return pathAggregate(y); }
  void cut(int x) { l[x] = p[l[access(x)]] = null; }
  void cut(int x, int y) { makeroot(y); cut(x); }
  void link(int x, int y) { makeroot(x); l[p[access(y)]=access(x)] = y; }
  void pathUpdate(int x, int y, int c) { int z = lca(x,y);
    if(x != z) carry[x] += c; if(y != z) carry[y] += c;
    val[z] += c; }
  inline int splay(int x) {
    for(push(x); p[x] != null; lift(x))
      if(l[l[p[p[x]]]] == x || r[r[p[p[x]]]] == x) lift(p[x]);
      else lift(x);
    return x; }
  void push(int x) {
    if(flip[x]==1) {
      swap(l[x], r[x]);
      flip[x]^=1; flip[l[x]]^=1; flip[r[x]]^=1; }
    val[x] += carry[x];
    carry[l[x]] += carry[x]; carry[r[x]] += carry[x];
    carry[x] = 0; }
  int update(int x) {
    if(x == null) return x;
    size[x] = size[l[x]] + size[r[x]] + 1;
    sum[x] = val[x]+sum[l[x]]+sum[r[x]] + carry[x]*size[x];
    return x; }
  int lca(int x, int y) {
    access(x); access(y); splay(x);
    return access(pp[x]==null?x:pp[x]); }
  void lift(int x) {
    if(p[x] == null) return;
    push(p[x]); push(x); push(l[x]); push(r[x]);
    pp[x] = pp[p[x]]; pp[p[x]] = null;
    int* a=&l[0], *b=&r[0];
    if(r[p[x]]==x) {a=&r[0]; b=&l[0];}
    a[p[x]] = b[x]; b[x] = p[x]; p[x] = p[p[x]];
    if(p[x] != null) {
      if(a[p[x]] == b[x]) a[p[x]] = x;
      else b[p[x]] = x; }
    if(a[b[x]] != null) p[a[b[x]]] = b[x];
    update(l[b[x]]); update(r[b[x]]);
    update(p[update(b[x])] = x); }
}; // from Antony at UCF.

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

	LinkCutTree lct;
	lct.init(n+1);
	for (char c; cin >> c && c != 'E'; ) {
		int a, b;
		cin >> a >> b;
		if (c == 'C') {
			lct.link(a,b);
		} else if (c == 'D') {
			lct.cut(a,b);
		} else {
			lct.makeroot(a);
			if (lct.findroot(b) == a) {
				cout << "YES" << endl;
			} else {
				cout << "NO" << endl;
			}
		}
	}

	return 0;
}
