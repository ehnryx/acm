#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/data_structure/segment_tree.h"
#include "../../../lca/tree/range_query_tree.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct Node {
  bool sum;
  void put(bool v) { sum = v; }
  int get() const { return sum; }
  void push(Node&, Node&) {}
  void pull(const Node& a, const Node& b) {
    sum = a.sum || b.sum;
  }
  bool contains() const { return sum; }
  static bool merge(bool a, bool b) { return a || b; }
  static bool default_value() { assert(false); }
};
using HLD = range_query_tree<segment_tree<Node, int>, int>;

int solve(int u, int ans, const vector<vector<int>>& adj, HLD& hld) {
  int rem = -1;
  bool down = hld.query_subtree(u);
  bool up = hld.query_path(u, 1, true, 0, Node::merge);
  if (!down) {
    if(!up) {
      ans++;
    } else {
      rem = hld.search_path(u, 1, true);
      hld.update_point(rem, 0);
    }
    hld.update_point(u, 1);
  }
  int res = ans;
  for(int v : adj[u]) {
    res = max(res, solve(v, ans, adj, hld));
  }
  if (!down) {
    if (rem != -1) {
      hld.update_point(rem, 1);
    }
    hld.update_point(u, 0);
  }
  return res;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<vector<int>> adj(n+1), other(n+1);
    for(int i=2; i<=n; i++) {
      int p;
      cin >> p;
      adj[p].push_back(i);
    }
    for(int i=2; i<=n; i++) {
      int p;
      cin >> p;
      other[p].push_back(i);
    }
    HLD hld(move(other), 1);
    cout << solve(1, 0, adj, hld) << nl;
  }

  return 0;
}
