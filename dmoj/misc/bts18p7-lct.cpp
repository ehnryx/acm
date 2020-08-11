// 120 minutes

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const char nl = '\n';

const int N = 1e5+7;
const int INF = 0x3f3f3f3f;

struct node; using pn = node*;
struct node { pn l, r, p, pp; int key, val, cnt, acc; bool rev;
	node(int k=0, int v=0);
	inline int dir() { return this == p->r; }
	inline void setc(pn c, bool right) { (right?r:l) = c; c->p = this; }
} dat[N];

pn nil = []() { pn x=dat; x->l = x->r = x->p = x;
	x->acc = -INF; x->cnt = 0; return x; } ();
node::node(int k, int v): l(nil), r(nil), p(nil), pp(nil),
	key(k), val(v), cnt(1), acc(v), rev(0) {}
int nodeid = 0; template <class... T> pn new_node(T&& ...args) {
	return &(dat[++nodeid] = node(forward<T>(args)...)); }

namespace SplayTree {
	void pull(pn x) { if(x!=nil) {
		x->cnt = 1 + x->l->cnt + x->r->cnt;
		x->acc = max(x->l->acc, max(x->val, x->r->acc));
	} }
	void rev(pn x) { if (x!=nil) { x->rev ^= 1; swap(x->l, x->r); } }
	void setpp(pn x, pn pp) { if(x!=nil) x->pp = pp; }
	void push(pn x) {
		if (x->rev) { rev(x->l); rev(x->r); x->rev=0; }
		setpp(x->l, x->pp); setpp(x->r, x->pp);
	}
	void rot(pn x) { pn p = x->p; push(p); push(x); bool d=x->dir();
		p->setc(d ? x->l : x->r, d); p->p->setc(x, p->dir()); x->setc(p, !d);
		pull(p); pull(x);
	}
	pn splay(pn x, pn to=nil) { if(x!=nil) { while(x->p!=to) {
		if(x->p->p!=to) { rot(x->dir() == x->p->dir() ? x->p : x); }
		rot(x); } } return x;
	}
	pn first(pn c) { if(splay(c)!=nil) {
		while(push(c), c->l!=nil) c=c->l; } return splay(c);
	}

	void pUpdate(pn x, ll v) { splay(x)->val += v; pull(x); }

	int rQuery(pn c, int k) {
		if(splay(c)->acc < k) return -1;
		for(;;) {
			while(push(c), c->l->acc >= k) { c = c->l; }
			if(c->val >= k) return c->key;
			c = c->r;
		}
	}

	struct LinkCutTree {
		vector<pn> nds;
		LinkCutTree(int n=0) { nds.resize(n, nil); for(int i=0; i<n; i++) nds[i] = new_node(i); }
		pn splitAfter(pn x) { push(x); push(x->r); pn bot = x->r;
			x->r = x->r->p = nil; pull(bot); pull(x); return bot; }
		void join(pn l, pn r) {
			pn x = splay(first(r)); x->pp = l->pp;
			push(x); push(splay(l)); x->setc(l,0); pull(x->l); pull(x); }
		pn access(pn x) { if(splay(x)->r != nil) { splitAfter(x)->pp = x; }
			for(pn w=x; pull(w), splay(w=x->pp)!=nil; splay(x)) {
				if(w->r!=nil) { splitAfter(w)->pp=w; } join(w,x); } return x;
		}
		void link(int x, int y) { join(access(nds[y]), reroot(nds[x])); }
		void cut(int x, int y) { reroot(nds[x]); access(nds[y]);
			splitAfter(splay(nds[x]))->pp = nil; }
		int findroot(int x) { return findroot(nds[x])->key; }
		pn findroot(pn x) { return first(access(x)); }
		void reroot(int x) { reroot(nds[x]); }
		pn reroot(pn x) { rev(access(x)); push(x); return x; }
		int query_path(int x, int y, int k) {
			reroot(nds[x]); access(nds[y]);
			int res = rQuery(nds[y], k);
			return res;
		}
		void insert_node(int x, ll v) { pUpdate(nds[x], v); }
	};
}

vector<int> rem[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m, r;
	cin >> n >> m >> r;

	SplayTree::LinkCutTree lct(n+1);

	for(int i=1; i<=n; i++) {
		int p;
		cin >> p;
		lct.insert_node(i, p);
	}

	vector<pair<int,int>> edges;
	for(int i=1; i<n; i++) {
		int a, b;
		cin >> a >> b;
		lct.link(a, b);
		edges.push_back(make_pair(a, b));
	}

	for(int i=0; i<r; i++) {
		int x, y;
		cin >> x >> y;
		rem[x].push_back(y-1);
	}

	for(int i=1; i<=m; i++) {
		int a, b, k;
		cin >> a >> b >> k;
		lct.reroot(a);
		if(lct.findroot(b) != a) {
		//if(lct.findroot(a) != lct.findroot(b)) {
			cout << -1 << nl;
		} else {
			cout << lct.query_path(a, b, k) << nl;
		}
		for(int j : rem[i]) {
			auto [u, v] = edges[j];
			lct.cut(u, v);
		}
	}

	return 0;
}
