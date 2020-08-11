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

////////////////////////////////////////////////////////////////////////
// Templated Segment Tree -- O(log(n)) per reasonable query
// Warning: possibly SLOW! because Node is copied when querying
// 
// The Node class requires the following: (SEE EXAMPLE BELOW)
// Node();
//  The default constructor that is called initially, and when a query
//  range is out of bounds.
// Node(T v);
//  The constructor that is called in set(int i, T v);
// bool put(T v);
//  The break condition when updating. For normal queries, return true.
// bool get();
//  The break condition when querying. For normal queries, return true.
// void update(T v, int len);
//  Used to update the Node with value v at a segment with length len.
// void push(Node& left, Node& right, int len);
//  Used to lazy propagate from current node with length len to left 
//  and right children.
// Node pull(Node left, Node right);
//  Used to update current node from left and right children.
//*!
template <class Node, class T>
struct SegmentTree {
    int n;
    vector<Node> segt;
    SegmentTree(int len) {
        n = 1 << (32 - __builtin_clz(len-1));
        segt.resize(2*n);
    }
    void set(int i, const T& v) {
        segt[n+i] = Node(v);
		for (int x=n+i; x>1; x>>=1) {
			segt[x>>1].pull(segt[x], segt[x^1]);
		}
    }
    void update(int l, int r, const T& v) {
        update(l, r, v, 1, 0, n-1);
    }
    void update(int l, int r, const T& v, int i, int s, int e) {
        if (e < l || s > r) return;
        if (l <= s && e <= r && segt[i].put(v)) {
            segt[i].update(v, e-s+1);
            return;
        }
        segt[i].push(segt[2*i], segt[2*i+1], e-s+1);
        int m = (s + e) / 2;
        update(l, r, v, 2*i, s, m);
        update(l, r, v, 2*i+1, m+1, e);
        segt[i].pull(segt[2*i], segt[2*i+1]);
    }
    Node query(int l, int r) {
        return query(l, r, 1, 0, n-1);
    }
    Node query(int l, int r, int i, int s, int e) {
        if (e < l || s > r) return Node();
        if (l <= s && e <= r && segt[i].get()) {
            return segt[i];
        }
        segt[i].push(segt[2*i], segt[2*i+1], e-s+1);
        int m = (s + e) / 2;
        return Node().pull(query(l, r, 2*i, s, m), query(l, r, 2*i+1, m+1, e));
    }
};
//*/

struct Node {
	ll sum, maxv, maxv2, maxcnt;
	bool lazy;
	Node(): sum(0), lazy(0), maxv(-INFLL), maxv2(-INFLL) {}
	Node(const ll& v): sum(v), maxv(v), maxv2(-INFLL), maxcnt(1), lazy(0) {}
	bool put(const ll& v) { return v > maxv2; }
	bool get() { return true; }
	// min update
	void update(const ll& v, int len) {
		if (v < maxv) {
			sum += maxcnt*(v-maxv);
			maxv = v;
			lazy = true;
		}
	}
	void push(Node& left, Node& right, int len) {
		if (lazy) {
			if (left.maxv > maxv) {
				left.sum += left.maxcnt*(maxv-left.maxv);
				left.maxv = maxv;
				left.lazy = true;
			}
			if (right.maxv > maxv) {
				right.sum += right.maxcnt*(maxv-right.maxv);
				right.maxv = maxv;
				right.lazy = true;
			}
			lazy = false;
		}
	}
	// sum query
	const Node& pull(const Node& left, const Node& right) {
		sum = left.sum + right.sum;
		if (left.maxv == right.maxv) {
			maxv = left.maxv;
			maxv2 = max(left.maxv2, right.maxv2);
			maxcnt = left.maxcnt + right.maxcnt;
		} else if (left.maxv > right.maxv) {
			maxv = left.maxv;
			maxv2 = max(left.maxv2, right.maxv);
			maxcnt = left.maxcnt;
		} else if (right.maxv > left.maxv) {
			maxv = right.maxv;
			maxv2 = max(right.maxv2, left.maxv);
			maxcnt = right.maxcnt;
		}
		return *this;
	}
};

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, q, a, b;
	cin >> n >> q;

	SegmentTree<Node,ll> segtree(n+1);

	ll offset = 0;
	for (int i=1; i<=n; i++) {
		cin >> a;
		segtree.set(i, a);
	}

	while (q--) {
		string s;
		cin >> s;
		if (s == "GROW") {
			cin >> a >> b;
			ll height = segtree.query(a,a).sum;
			segtree.set(a, height+b);
		} else if (s == "CUT") {
			cin >> a;
			ll before = segtree.query(1,n).sum - n*offset;
			segtree.update(1,n,a+offset);
			ll after = segtree.query(1,n).sum - n*offset;
			cout << before-after << nl;
		} else {
			cin >> a;
			offset -= a;
		}
	}

	return 0;
}
