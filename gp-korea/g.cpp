#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using vi = vector<int>;
const char nl = '\n';

const int N = 4e5+17;
int a[N], b[N], c[N];

struct Max2 {
	int c, c2;
	int e, e2;
	Max2(): c(0), c2(0), e(), e2() {}
	void combine(const Max2& o) {
		update(o.c, o.e);
		update(o.c2, o.e2);
	}
	void update(int cost, int edge) {
		if(cost > c) {
			c2 = c;
			e2 = e;
			c = cost;
			e = edge;
		} else if(cost > c2) {
			c2 = cost;
			e2 = edge;
		}
	}
	int query(int u) {
		if(a[e] != u && b[e] != u) return e;
		else return e2;
	}
};

struct node; using pn = node*;
struct node { pn l, r, p, pp; Max2 val, acc; int cnt; bool rev;
	node();
	inline int dir() {return this == p->r;}
	inline void setc(pn c, bool right) {(right?r:l) = c; c->p = this;}
} dat[N];

pn nil=[](){pn x=dat; x->l=x->r=x->p=x; // x->acc=INF;  //RMQ
	x->cnt=0; return x;}();
node::node(): l(nil), r(nil), p(nil), pp(nil),
	val(), cnt(1), acc(), rev(0) {}
int nodeid = 0; template <class... T> pn new_node(T&& ...args) {
	return &(dat[++nodeid] = node(forward<T>(args)...));	}

namespace SplayTree {
//%%==
inline void pull(pn x) {if(x!=nil) {
	x->cnt = 1 + x->l->cnt + x->r->cnt;
	x->acc = x->val;
	x->acc.combine(x->l->acc);
	x->acc.combine(x->r->acc);
}}
//%%==
void rev(pn x) { if(x != nil) { x->rev ^= 1; swap(x->l, x->r); } }
inline void setpp(pn x, pn pp) { if(x!=nil) x->pp = pp; } // LCT
inline void push(pn x) {
	if (x->rev) { rev(x->l); rev(x->r); x->rev=0; } // REV
	setpp(x->l, x->pp); setpp(x->r, x->pp);  // LCT
}
// core splay tree
inline void rot(pn x) { pn p = x->p; push(p); push(x); bool d=x->dir();
	p->setc(d ? x->l : x->r, d); p->p->setc(x, p->dir()); x->setc(p, !d);
	pull(p); pull(x); }

pn splay(pn x, pn to=nil) { if (x!=nil) { while (x->p!=to) {
	if (x->p->p!=to) rot(x->dir() == x->p->dir() ? x->p : x); rot(x); }}
	return x; }
pn del(pn y) { pn x=splay(y)->r; if (x==nil) x=y->l; else {
	while (push(x), x->l != nil) x = x->l; splay(x,y)->setc(y->l,0); }
	x->p=nil; pull(x); return x; }

pn first(pn c) { if(splay(c) != nil)
	while(push(c), c->l != nil) c=c->l; return splay(c); }

pn range(pn c, pn l, pn r) { if (l == nil) {
	if (r==nil) return splay(c); return splay(r)->l; }
	if (l==r) return nil; splay(l);
	if (r==nil) return l->r; return splay(r,l)->l;}
Max2 rQuery(pn c, pn l, pn r) { return range(c, l, r)->acc; }
void pUpdate(pn x, int cost, int edge) {
	splay(x)->val.update(cost, edge); pull(x);
}

struct LinkCutTree {
	vector<pn> nds;
	LinkCutTree(int n=0) { init(n); }
	void init(int n) { nds.resize(n, nil);
		for(int i=0; i<n; i++) nds[i] = new_node(); }
	pn splitAfter(pn x) { push(x); push(x->r); pn bot = x->r;
		x->r = x->r->p = nil; pull(bot); pull(x); return bot; }
	void join(pn l, pn r) { pn x = splay(first(r)); x->pp = l->pp;
		push(x); push(splay(l)); x->setc(l, 0); pull(x->l); pull(x); }
	pn access(pn x) { if(splay(x)->r != nil) { splitAfter(x)->pp = x; }
		for(pn w=x; pull(w), splay(w=x->pp)!=nil; splay(x)) {
			if(w->r!=nil) { splitAfter(w)->pp=w; } join(w,x); } return x; }
	void link(int x, int y) { join(access(nds[y]), reroot(nds[x])); }
	void cut(int x, int y) { reroot(nds[x]); access(nds[y]);
		splitAfter(splay(nds[x]))->pp = nil; }
	pn reroot(pn x) { rev(access(x)); push(x); return x; }

	Max2 query_path(int x, int y) { reroot(nds[x]); access(nds[y]);
		return rQuery(nds[x], nil, nil); }
	void insert_node(int x, int cost, int edge) {
		pUpdate(nds[x], cost, edge);
	}
};
}

int dsu[N];
int find(int i) {
	if(dsu[i] == -1) return i;
	return dsu[i] = find(dsu[i]);
}
int link(int i, int j) {
	if(find(i) == find(j)) return false;
	dsu[find(i)] = find(j);
	return true;
}

bool in[N];
pair<int,int> memo[N];
vector<int> adj[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m;
	cin >> n >> m;
	SplayTree::LinkCutTree lct(n+m+7);

	vector<pair<int,int>> edges;
	for(int i=0; i<m; i++) {
		cin >> a[i] >> b[i] >> c[i];
		edges.push_back(make_pair(c[i], i));
		adj[a[i]].push_back(i);
		adj[b[i]].push_back(i);
		lct.insert_node(i, c[i], i);
	}
	sort(edges.begin(), edges.end());

	memset(dsu, -1, sizeof dsu);
	ll ans = 0;
	for(const auto& sad : edges) {
		int i = sad.second;
		if(link(a[i],b[i])) {
			lct.link(i, m+a[i]);
			lct.link(i, m+b[i]);
			in[i] = true;
			ans += c[i];
		}
	}

	int id = 0;
	for(int s=1; s<=n; s++) {
		//cerr<<"SOLVE "<<s<<nl;
		while(id > 0) {
			//cerr<<"id = "<<id<<nl;
			int e, f;
			tie(e, f) = memo[--id];
			//cerr<<"redo "<<e<<" with "<<f<<nl;
			assert(in[e] && !in[f]);
			lct.cut(e, m+a[e]);
			lct.cut(e, m+b[e]);
			lct.link(f, m+a[f]);
			lct.link(f, m+b[f]);
			in[e] = false;
			in[f] = true;
			ans += c[f] - c[e];
		}
		for(int e : adj[s]) {
			if(in[e]) continue;
			//cerr<<"QUERY PATH "<<a[e]<<" + "<<b[e]<<endl;
			Max2 path = lct.query_path(m + a[e], m + b[e]);
			int f = path.query(s);
			//cerr<<"replace "<<f<<" with "<<e<<nl;
			assert(in[f]);
			//cerr<<"CUT"<<endl;
			lct.cut(f, m+a[f]);
			lct.cut(f, m+b[f]);
			//cerr<<"LINK"<<endl;
			lct.link(e, m+a[e]);
			lct.link(e, m+b[e]);
			//cerr<<"DONE"<<endl;
			in[f] = false;
			in[e] = true;
			memo[id++] = make_pair(e,f);
			ans += c[e] - c[f];
		}
		cout << ans << nl;
		//cerr << endl;
	}

	return 0;
}
