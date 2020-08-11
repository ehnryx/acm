#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Node {
	Node* l;
	Node* r;
	int len;
	int col, prec, sufc;
	int pre, suf, res;

	Node(int n): len(n) {
		l = r = nullptr;
		prec = sufc = col = INF;
		pre = suf = res = 0;
	}

	void pull() {
		// col
		if (l->col == r->col) {
			col = l->col;
		} else {
			col = INF;
		}
		prec = l->prec;
		sufc = r->sufc;

		// res
		res = max(l->res, r->res);
		if (l->sufc == r->prec) {
			res = max(res, l->suf + r->pre);
		}
		if (l->col == r->prec) pre = l->len + r->pre;
		else pre = l->pre;
		if (r->col == l->sufc) suf = l->suf + r->len;
		else suf = r->suf;
	}

	void insert(int x, int v) {
		if (len == 1) {
			prec = sufc = col = v;
			pre = suf = res = 1;
			return;
		}
		if (l == nullptr) l = new Node(len/2);
		if (r == nullptr) r = new Node(len/2);
		if (x<=len/2) {
			l->insert(x, v);
		} else {
			r->insert(x-len/2, v);
		}
		pull();
	}

	int get(int x) {
		if (len == 1) {
			return col;
		} else if (x<=len/2) {
			return l->get(x);
		} else {
			return r->get(x-len/2);
		}
	}

	int query() {
		return res;
	}

};

Node* combine(Node* l, Node* r) {
	assert(l->len == r->len);
	Node* p = new Node(l->len + r->len);
	p->l = l;
	p->r = r;
	p->pull();
	return p;
}

const int N = 4e5+1;
Node* root[N];
int ans[N];
bool dead[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, q;
	cin >> n >> q;

	for (int i=1; i<=n; i++) {
		int s;
		cin >> s;
		root[i] = new Node(s);
		for (int j=1; j<=s; j++) {
			int v;
			cin >> v;
			root[i]->insert(j, v);
		}
		ans[i] = root[i]->query();
	}

	int id = n;
	while (q--) {
		int t;
		cin >> t;
		if (t==1) {
			int a, b, i;
			cin >> a >> b >> i;
			assert(!dead[i]);
			int va = root[i]->get(a);
			int vb = root[i]->get(b);
			root[i]->insert(a, vb);
			root[i]->insert(b, va);
			ans[i] = root[i]->query();
		} else if (t==2) {
			int l, r;
			cin >> l >> r;
			assert(!dead[l] && !dead[r]);
			root[++id] = combine(root[l], root[r]);
			ans[id] = root[id]->query();
			dead[l] = dead[r] = true;
		} else if (t==3) {
			int i;
			cin >> i;
			assert(!dead[i]);
			root[++id] = root[i]->l;
			ans[id] = root[id]->query();
			root[++id] = root[i]->r;
			ans[id] = root[id]->query();
			dead[i] = true;
		} else {
			int i;
			cin >> i;
			assert(!dead[i]);
			cout << ans[i] << nl;
		}
	}

	return 0;
}
