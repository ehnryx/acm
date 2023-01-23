#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';
using ll = long long;

struct Line {
  mutable ll m, b, p;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  static const ll inf = LLONG_MAX;
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) { x->p = inf; return false; }
    if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
    else x->p = div(y->b - x->b, x->m - y->m);
    return x->p >= y->p;
  }
  void add(ll m, ll b) {
    auto z = insert({m, b, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  ll query(ll x) const {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.m * x + l.b;
  }
  LineContainer() = default;
};

struct Node {
  static const int inf = 0x3f3f3f3f;
  LineContainer lc;
  Node() = default;
  int get(int x) const { return -lc.query(x); }
  void push(Node&, Node&) {}
  void pull(const Node&, const Node&) {}
  static int default_value() { assert(false); }
  static int merge(int a, int b) { return min(a, b); }
};

void insert(segment_tree<Node, int>& st, int x, int m, int b) {
  m = -m; b = -b;
  st[x += st.length].lc.add(m, b);
  for(x/=2; x; x/=2) {
    st[x].lc.add(m, b);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<int> a(n+1), s(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  partial_sum(begin(a), end(a), begin(s));
  segment_tree<Node, int> st(n+1);
  for(int i=1; i<=n; i++) {
    insert(st, i, -a[i], i*a[i] - s[i-1]);
  }

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    int x, y;
    cin >> x >> y;
    int left = y - x + 1;
    int right = y;
    cout << s[right] + st.query(left, right, left) << nl;
  }

  return 0;
}
