#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<17;

struct SegTree {
	struct Node {
		int v;
		Node *l, *r;
		Node(int _v=INF): v(_v) {
			l = r = nullptr;
		}
	};
	Node* root;
	SegTree() {
		root = new Node();
	}

	void push(Node* i, int s, int e) {
		if(i->v < INF) {
			if(i->l == nullptr) i->l = new Node(i->v);
			else i->l->v = i->v;
			if(i->r == nullptr) i->r = new Node(i->v + (e-s+1)/2);
			else i->r->v = i->v + (e-s+1)/2;
			i->v = INF;
		}
	}

	void insert(int l, int r, int v) {
		insert(l,r,v,root,0,N-1);
	}
	Node* insert(int l, int r, int v, Node* i, int s, int e) {
		if(r<s || e<l) return nullptr;
		if(i == nullptr) i = new Node();
		if(l<=s && e<=r) {
			i->v = v + s-l;
			return i;
		}
		push(i,s,e);
		int m = (s+e)/2;
		Node* left = insert(l,r,v,i->l,s,m);
		if(i->l == nullptr) i->l = left;
		Node* right = insert(l,r,v,i->r,m+1,e);
		if(i->r == nullptr) i->r = right;
		return i;
	}

	int query(int x) {
		return query(x, root, 0, N-1);
	}
	int query(int x, Node* i, int s, int e) {
		if(i==nullptr) return INF;
		if(s==e) {
			return i->v;
		}
		push(i,s,e);
		int m = (s+e)/2;
		if(x<=m) return query(x, i->l, s, m);
		else return query(x, i->r, m+1, e);
	}
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin >> n >> m;
	int a[n+1],b[n+1];

	for(int i=1;i<=n;i++) {
		cin>>a[i];
	}
	for(int i=1;i<=n;i++) {
		cin>>b[i];
	}

	SegTree st;
	for(int i=0;i<m;i++) {
		int t;
		cin >> t;
		if(t==1) {
			int x,y,k;
			cin >> x >> y >> k;
			st.insert(y, y+k-1, x);
		} else {
			int x;
			cin >> x;
			int j = st.query(x);
			if(j >= INF) cout << b[x] << nl;
			else cout << a[j] << nl;
		}
	}

	return 0;
}
