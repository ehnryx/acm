#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';
using ll = long long;

struct Node {
  ll start, end, value;
  Node() = default;
  Node(pair<ll,ll> se): start(se.first), end(se.second), value(0) {}
  const Node& get() const { return *this; }
  void push(Node&, Node&) {}
  const Node& pull(const Node& a, const Node& b) {
    value = max(a.value, b.value);
    value = max(value, a.start + b.end);
    start = max(a.start, b.start);
    end = max(a.end, b.end);
    return *this;
  }
  static Node default_value() { assert(false); }
  static Node merge(const Node& a, const Node& b) { return Node().pull(a, b); }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  vector<ll> d(2*n+1), h(2*n+1);
  for(int i=1; i<=n; i++) {
    cin >> d[i];
    d[i + n] = d[i];
  }
  for(int i=1; i<=n; i++) {
    cin >> h[i];
    h[i + n] = h[i];
  }
  partial_sum(begin(d), end(d), begin(d));

  vector<pair<ll,ll>> v(2*n+1);
  for(int i=1; i<=2*n; i++) {
    v[i] = pair(2*h[i] - d[i-1], 2*h[i] + d[i-1]);
  }
  segment_tree<Node,Node>  st(v);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    swap(a, b);
    a += 1;
    b -= 1;
    if(b < a) {
      b += n;
    }
    cout << st.query(a, b).value << nl;
  }

  return 0;
}
