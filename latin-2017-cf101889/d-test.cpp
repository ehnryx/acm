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
// Templated Simple Segment Tree -- O(log(n)) per query (UNTESTED)
// Warning: possibly SLOW! because Node is copied when querying
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
    }
    void build() {
        for (int i = n-1; i > 0; i--) {
            segt[i].pull(segt[2*i], segt[2*i+1]);
        }
    }

    void update(int l, int r, const T& v) {
        update(l, r, v, 1, 0, n-1);
    }
    void update(int l, int r, const T& v, int i, int s, int e) {
        if (e < l || s > r) return;
        if (l <= s && e <= r && segt[i].put()) {
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

const int N = 1e5+1;
int cnt[N];

struct Node {
	int colour;
	Node(int x = 0): colour(x) {}
	bool get() { return true; }
	bool put() { return colour != -1; }
	void update(int v, int len) {
		cnt[colour] -= len;
		colour = v;
		cnt[colour] += len;
	}
	void push(Node& left, Node& right, int len) {
		if (colour != -1) {
			left.colour = right.colour = colour;
		}
	}
	const Node& pull(const Node& left, const Node& right) {
		if (left.colour == right.colour) colour = left.colour;
		else colour = -1;
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

	int l, c, n, p, x, a, b;
	cin >> l >> c >> n;

	SegmentTree<Node, int> segt(l);
	cnt[1] = l;
	for (int i=0; i<l; i++) {
		segt.set(i, 1);
	}
	segt.build();

	for (int i=0; i<n; i++) {
		cin >> p >> x >> a >> b;
		ll s = cnt[p];
		int m1 = (a+s*s) % l;
		int m2 = (a+(s+b)*(s+b)) % l;
		if (m1 > m2) swap(m1,m2);
		segt.update(m1, m2, x);
	}

	int ans = 0;
	for (int i=1; i<=c; i++) {
		ans = max(ans, cnt[i]);
	}
	cout << ans << nl;

	return 0;
}
