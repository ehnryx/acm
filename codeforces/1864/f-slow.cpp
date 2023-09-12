#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "ds/segment_tree.h"
%:include "ds/segment_tree_nodes_min.h"
%:include "ds/segment_tree_nodes_sum.h"
%:include "ds/splay_tree.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct Event {
  int l, r, i;
  bool operator<(const Event& o) const {
    return r < o.r;
  }
};

using splay_set = splay_tree<splay_node<int, void>>;

struct node_t {
  using out_t = int;
  splay_set st;
  node_t() = default;
  void put(int v) {
    st.insert(v);
  }
  int get(int lb) {
    auto x = st.lower_bound(lb);
    return st.size() - st.rank(x);
  }
  static int merge(int a, int b) { return a + b; }
};

using max_tree = segment_tree<segment_tree_nodes::point_assign_range_min<int, greater<>>>;
using sum_tree = segment_tree<segment_tree_nodes::point_assign_range_sum<int>>;
using sad_tree = segment_tree<node_t>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, q;
  cin >> n >> q;
  vector<int> a(n+1);
  vector<vector<int>> idxs(n+2);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    idxs[a[i]].push_back(i);
  }
  vector<Event> ev;
  for(int i=0; i<q; i++) {
    int l, r;
    cin >> l >> r;
    ev.emplace_back(l, r, i);
  }
  sort(begin(ev), end(ev));

  max_tree cuts(n+1);
  sad_tree contribution(n+1);
  sum_tree parts(n+1);

  vector<int> ans(q);
  for(int v=1, eid=0; v<=n+1; v++) {
    while(eid < size(ev) and ev[eid].r < v) {
      ans[ev[eid].i] = parts.query_range(ev[eid].l, ev[eid].r) - contribution.query_range(0, ev[eid].l - 1, ev[eid].l);
      eid++;
    }

    if(empty(idxs[v])) continue;
    const auto& idx = idxs[v];

    int cur_parts = 1;
    for(int i=1; i<size(idx); i++) {
      int cut = cuts.query_range(idx[i-1], idx[i]);
      if(cut == 0) continue;
      contribution.update_up(cut, v);
      cur_parts++;
    }
    parts.update_point(v, cur_parts);

    for(int i : idx) {
      cuts.update_point(i, v);
    }
  }

  for(int i=0; i<q; i++) {
    cout << ans[i] << nl;
  }
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
