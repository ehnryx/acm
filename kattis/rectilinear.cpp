#include <bits/stdc++.h>
using namespace std;

%:include "utility/defines.h"
%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "ds/segment_tree.h"
%:include "ds/segment_tree_nodes_sum.h"
%:include "ds/union_find.h"
%:include "geometry/point.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using pt = point<int>;

struct node final : segment_node::custom_update_range_sum<int> {
  using base = segment_node::custom_update_range_sum<int>;
  using base::base;
  void put(int v) { sum += v; }
};

void solve(auto& cin) {
  int n;
  cin >> n;
  map<int, vector<int>> vs;
  map<int, int> remap;
  vector<pair<pt, int>> v;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    v.emplace_back(pt(x, y), i);
    vs[x].push_back(y);
    remap[y];
  }
  int rid = 0;
  for(auto& it : remap) {
    it.second = rid++;
  }
  assert(rid);

  segment_tree<node> st(rid);

  ll ans = 0;
  int last = 0;
  for(auto& [x, ys] : vs) {
    sort(begin(ys), end(ys));
    if(unique(begin(ys), end(ys)) != end(ys)) {
      cout << -1 << nl;
      return;
    }
    if(size(ys) % 2) {
      cout << -1 << nl;
      return;
    }

    ans += (ll)st.query(0, rid - 1) * (x - last);
    for(int i=1; i<size(ys); i+=2) {
      ans += ys[i] - ys[i-1];
      int a = remap[ys[i-1]];
      int b = remap[ys[i]];
      if(a+1 <= b-1 && st.query(a+1, b-1)) {
        cout << -1 << nl;
        return;
      }
      if(st.query_point(a)) {
        st.update_point(a, -1);
      } else {
        st.update_point(a, 1);
      }
      if(st.query_point(b)) {
        st.update_point(b, -1);
      } else {
        st.update_point(b, 1);
      }
    }
    last = x;
  }

  if(st.query(0, rid - 1)) {
    cout << -1 << nl;
    return;
  }

  union_find dsu(n);
  int g = n;
  sort(begin(v), end(v), [](const auto& a, const auto& b) {
      return pt::by_x()(a.first, b.first); });
  for(int i=1; i<n; i+=2) {
    assert(v[i-1].first.x == v[i].first.x);
    g -= dsu.link(v[i].second, v[i-1].second);
  }
  sort(begin(v), end(v), [](const auto& a, const auto& b) {
      return pt::by_y()(a.first, b.first); });
  for(int i=1; i<n; i+=2) {
    assert(v[i-1].first.y == v[i].first.y);
    g -= dsu.link(v[i].second, v[i-1].second);
  }

  if(g > 1) {
    cout << -1 << nl;
    return;
  }

  cout << ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  while(T--) {
    solve(cin);
  }

  return 0;
}
