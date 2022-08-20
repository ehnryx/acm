#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"

%:include "ds/segment_tree.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct node {
  using out_t = pair<int, int>;
  int lb, rb;
  bool lazy = false;
  node() = default;
  node(pair<int, int> x): lb(x.first), rb(x.second) {}
  pair<int, int> get() const { return pair(lb, rb); }
  void put(pair<int, int> x) { put(x.first, x.second); }
  void put(int left, int right) {
    lb = left;
    rb = right;
    lazy = true;
  }
  void push(node& left, node& right) {
    if(lazy) {
      left.put(lb, rb);
      right.put(lb, rb);
      lazy = false;
    }
  }
  void pull(const node& left, const node& right) {
    lb = min(left.lb, right.lb);
    rb = max(left.rb, right.rb);
  }
  static out_t merge(out_t a, out_t b) {
    return pair(min(a.first, b.first), max(a.second, b.second));
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  const int M = 1e6 + 1;

  int n, m;
  cin >> n >> m;
  vector<tuple<int, int, int>> ev;
  for(int i=0; i<n; i++) {
    int x, y, r;
    cin >> x >> y >> r;
    ev.emplace_back(y, x - r, x + r);
  }
  sort(begin(ev), end(ev));

  vector<pair<int, int>> init(M);
  set<int> have;
  for(int i=0; i<M; i++) {
    init[i] = pair(i, i);
    have.insert(i);
  }

  segment_tree<node> st(init);
  for(auto [_, l, r] : ev) {
    assert(0 <= l && r < M);
    int mid = (l + r) / 2;
    auto left = st.query_point(l);
    auto right = st.query_point(r);
    st.update(l, mid - 1, left);
    st.update(mid + 1, r, right);
    st.update_point(mid, node::merge(left, right));
  }

  reverse(begin(ev), end(ev));
  for(auto [_, l, r] : ev) {
    int mid = (l + r) / 2;
    if(have.upper_bound(l) != have.upper_bound(mid)) {
      have.insert(l);
    }
    if(have.lower_bound(mid) != have.lower_bound(r)) {
      have.insert(r);
    }
    auto it = have.upper_bound(l);
    while(it != have.end() && *it < r) {
      it = have.erase(it);
    }
  }

  vector<int> ones(M), sum(M + 1);
  for(auto it : have) {
    ones[it] = 1;
  }
  partial_sum(begin(ones), end(ones), begin(sum) + 1);

  for(int i=0; i<m; i++) {
    int l, r;
    cin >> l >> r;
    tie(l, r) = st.query(l, r);
    cout << sum[r + 1] - sum[l] << nl;
  }

  return 0;
}
