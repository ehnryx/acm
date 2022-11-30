#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "tree/compressed_tree.h"
%:include "tree/range_query_tree.h"
%:include "ds/segment_tree.h"
%:include "ds/segment_tree_nodes_sum.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using segtree = segment_tree<segment_node::range_add_range_sum<ll>>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<vector<int>> group(n+1);
  for(int i=1; i<=n; i++) {
    int c;
    cin >> c;
    group[c].push_back(i);
  }
  vector<vector<int>> adj(n+1);
  vector<pair<int, int>> edges;
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    edges.emplace_back(a, b);
  }

  range_query_tree<segtree, segtree::Query_t> tree(adj, 1);
  for(int i=1; i<=n; i++) {
    if(size(group[i]) <= 1) continue;
    //cerr << "GROUP " << i << " -> "; for(int v : group[i]) cerr << v << " ";
    //cerr << nl;
    compressed_tree ct(tree, group[i]);
    auto update = [&](auto&& self, int u) -> int {
      int sub = ct.given[u];
      for(auto [v, _] : ct[u]) {
        sub += self(self, v);
      }
      if(u) {
        int at = ct.vertices[u];
        int par = ct.vertices[ct.parent[u].first];
        //cerr << "UPDATE " << at << " " << par << " w/ " << sub << " * " << size(group[i])-sub << nl;
        tree.update_path(at, par, false, (ll)sub * (size(group[i]) - sub));
      }
      return sub;
    };
    update(update, 0);
    //cerr << nl;
  }

  for(auto [a, b] : edges) {
    if(tree.is_ancestor_of(a, b)) {
      swap(a, b);
    }
    //cerr << "QUERY " << a << " ";
    cout << tree.query_point(a) << " ";
    //cerr << nl;
  }
  cout << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
