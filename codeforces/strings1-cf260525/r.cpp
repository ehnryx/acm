#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "string/suffix_tree.h"
%:include "tree/range_query_tree.h"
%:include "data_structure/segment_tree.h"
%:include "data_structure/segment_tree_nodes_min.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct Item {
  int val, len;
  bool operator>(const Item& o) const {
    return val > o.val or (val == o.val and len < o.len);
  }
};

using min_node = segment_tree_nodes::range_min_range_min<int>;
using max_node = segment_tree_nodes::range_min_range_min<Item, greater<Item>>;
enum class Q { VALUE, INDEX };
struct ds {
  ds(int n): ans(n), idx(n, n) {}
  auto query_point(int i, Q q) {
    assert(q == Q::VALUE);
    return ans.query_point(i);
  }
  auto query_range(int i, int j, Q q) {
    assert(q == Q::INDEX);
    return idx.query_range(i, j);
  }
  void update_point(int i, Q q, auto... v) {
    assert(q == Q::INDEX);
    idx.update_point(i, v...);
  }
  void update_range(int i, int j, Q q, auto... v) {
    assert(q == Q::VALUE);
    ans.update_range(i, j, v...);
  }
  segment_tree<max_node> ans;
  segment_tree<min_node> idx;
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  string s;
  cin >> s;
  suffix_tree st(s);

  const int L = 32 - __builtin_clz(s.size());
  vector anc(st.size(), vector(L, -1)), length(st.size(), vector(L, 0));
  auto build = [&,uid=0](auto&& self, int u) mutable -> void {
    for(int j=1; j<L and anc[u][j-1] != -1; j++) {
      anc[u][j] = anc[anc[u][j-1]][j-1];
      length[u][j] = length[anc[u][j-1]][j-1] + length[u][j-1];
    }
    for(auto [c, v] : st[u]) {
      anc[v][0] = u;
      length[v][0] = st.length(v);
      self(self, v);
    }
  };
  build(build, st.root());

  auto jump = [&](int u, int len) {
    len = n - u - len;
    for(int j=L-1; j>=0; j--) {
      if(anc[u][j] != -1 and length[u][j] <= len) {
        len -= length[u][j];
        u = anc[u][j];
      }
    }
    return u;
  };

  vector<vector<int>> adj(st.size());
  for(int i=0; i<st.size(); i++) {
    if(i != st.root()) {
      adj[st.parent(i)].push_back(i);
    }
  }
  range_query_tree<ds> rqt(adj, st.root());

  int ans = 0;
  for(int i=n-1; i>=0; i--) {
    auto [val, len] = rqt.query_point(i, Q::VALUE);
    if(val) {
      int j = rqt.query_subtree(jump(i, len), Q::INDEX);
      len += j - i;
    } else {
      len = 1;
    }
    rqt.update_point(i, Q::INDEX, i);
    rqt.update_subtree(jump(i, len), Q::VALUE, Item{ val + 1, len });
    ans = max(ans, val + 1);
  }

  cout << ans << nl;
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
