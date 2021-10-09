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
// USAGE:
//   SegmentTree<Node,T> magic(length);
//   magic.set(i,v); sets ith value to v, DOES NOT PULL
//   magic.build(); pulls leaves up
//   magic.query(l,r); range [l,r], combines segments using pull
//   magic.update(l,r,v); range [l,r], updates with v
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
        if (l <= s && e <= r && segt[i].put(v)) {
            segt[i].update(v, e-s+1);
            // if (i<n) segt[i].pull(segt[2*i], segt[2*i+1]);
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
  int val;
  Node(int v=0): val(v) {}
  bool put(int v) { return true; }
  bool get() { return true; }
  void update(int v, int len) { val = v; }
  void push(Node& left, Node& right, int len) {}
  Node pull(const Node& left, const Node& right) {
    val = left.val + right.val;
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

  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    SegmentTree<Node,int> segt(n+m+1);
    int pos[n+1];
    for (int i=1; i<=n; i++) {
      segt.set(n-i, 1);
      pos[i] = n-i;
    }
    segt.build();

    int top = n;
    for (int i=0; i<m; i++) {
      int a;
      cin >> a;
      cout << segt.query(pos[a]+1,top).val << " ";
      segt.update(pos[a], pos[a], 0);
      segt.update(top, top, 1);
      pos[a] = top++;
    }
    cout << nl;
  }

  return 0;
}
