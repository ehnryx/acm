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

const int N = 1e5+7;

struct node; using pn = node*;
struct node { pn l,r,p,pp; int key, cnt; bool rev;
	node(int k=0);
	inline int dir() { return this == p->r; }
	inline void setc(pn c, bool right) { (right?r:l)=c; c->p=this; }
} dat[N];
pn nil=[]() { pn x=dat; x->l = x->r = x->p = x;
	x->cnt = 0; return x; } ();
node::node(int k): l(nil), r(nil), p(nil), pp(nil),
	key(k), cnt(1), rev(0) {}
int nodeid = 0; template <class... T> pn new_node(T&& ...args) {
	return &(dat[++nodeid] = node(forward<T>(args)...)); }

namespace SplayTree {
	inline void pull(pn x) { if(x!=nil) {
		x->cnt = 1 + x->l->cnt + x->r->cnt; }
	}
	inline void rev(pn x) {
		if(x != nil) { x->rev ^= 1; swap(x->l, x->r); }
	}
	inline void setpp(pn x, pn pp) { if(x!=nil) x->pp = pp; }
	inline void push(pn x) {
		if(x->rev) { rev(x->l); rev(x->r); x->rev = 0; }
		setpp(x->l, x->pp); setpp(x->r, x->pp);
	}
	inline void rot(pn x) {
		pn p = x->p; push(p); push(x); bool d = x->dir();
		p->setc(d ? x->l : x->r, d); p->p->setc(x, p->dir());
		x->setc(p, !d); pull(p); pull(x);
	}
	pn splay(pn x, pn to=nil) {
		if(x!=nil) { while (x->p!=to) {
		if(x->p->p!=to) rot(x->dir() == x->p->dir() ? x->p : x);
		rot(x); } } return x;
	}
	pn first(pn c) { if (splay(c) != nil) {
		while (push(c), c->l!=nil) c=c->l; } return splay(c);
	}

	struct LinkCutTree { vector<pn> nds;
		LinkCutTree(int n=0) { init(n); }
		void init(int n) { nds.resize(n, nil);
			for(int i=0; i<n; i++) nds[i] = new_node(i);
		}
		pn splitAfter(pn x) {
			push(x); push(x->r); pn bot=x->r;
			x->r = x->r->p = nil; pull(bot); pull(x); return bot;
		}
		void join(pn l, pn r) { pn x = splay(first(r)); x->pp = l->pp;
			push(x); push(splay(l)); x->setc(l,0); pull(x->l); pull(x);
		}
		pn access(pn x) {
			if(splay(x)->r != nil) { splitAfter(x)->pp = x; }
			for(pn w=x; pull(w), splay(w=x->pp)!=nil; splay(x)) {
				if(w->r!=nil) { splitAfter(w)->pp = w; }
				join(w,x); } return x;
		}
		void link(int x, int y) {
			join(access(nds[y]), reroot(nds[x]));
		}
		void cut(int x, int y) { reroot(nds[x]); access(nds[y]);
			splitAfter(splay(nds[x]))->pp = nil; }
		void reroot(int x) { reroot(nds[x]); }
		pn reroot(pn x) { rev(access(x)); push(x); return x; }
		int findroot(int x) { return findroot(nds[x])->key; }
		pn findroot(pn x) { return first(access(x)); }
	};
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

	SplayTree::LinkCutTree lct;
	lct.init(n+1);

	for (char c; cin >> c && c != 'E'; ) {
		int a, b;
		cin >> a >> b;
		if (c == 'C') {
			lct.link(a,b);
		} else if (c == 'D') {
			lct.cut(a,b);
		} else {
			lct.reroot(a);
			if (lct.findroot(b) == a) {
				cout << "YES" << endl;
			} else {
				cout << "NO" << endl;
			}
		}
	}

	return 0;
}
