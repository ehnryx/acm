#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';
using ll = long long;

struct Node {
  ll value, lazy;
  Node() = default;
  void put(ll v) {
    value += v;
    lazy += v;
  }
  ll get() const { return value; }
  void push(Node& a, Node& b) {
    if(lazy) {
      a.put(lazy);
      b.put(lazy);
      lazy = 0;
    }
  }
  void pull(const Node& a, const Node& b) {
    value = max(a.value, b.value);
  }
  static ll merge(ll a, ll b) { return max(a, b); }
  static ll default_value() { assert(false); }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  vector<int> cost(n+1);
  for(int i=1; i<=n; i++) {
    cin >> cost[i];
  }
  vector<vector<pair<int,int>>> profit(n+1);
  for(int i=0; i<m; i++) {
    int l, r, v;
    cin >> l >> r >> v;
    profit[r].emplace_back(l, v);
  }

  segment_tree<Node, ll> st(n+2);
  vector<ll> dp(n+1);
  for(int i=1; i<=n; i++) {
    st.update(1, i, -cost[i]);
    for(auto [l, v] : profit[i]) {
      st.update(1, l, v);
    }
    dp[i] = max(dp[i-1], st.query(1, i));
    st.update_point(i+1, dp[i]);
  }
  cout << dp[n] << nl;

  return 0;
}
