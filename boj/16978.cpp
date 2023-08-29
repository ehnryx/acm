#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

template <typename node_t>
struct persistent_segment_tree {
  int n;
  vector<node_t> data;
  vector<int> root;
  template <typename U>
  persistent_segment_tree(const vector<U>& a, int r = 0)
    : n(a.size() == 1 ? 1 : 1 << (32 - __builtin_clz(a.size() - 1))) {
    data.reserve(r + 2);
    data.emplace_back(); // nil
    data.emplace_back(); // v0 root
    root.emplace_back(1);
    for(int i=0; i<a.size(); i++) {
      update_point<true>(0, i, a[i]);
    }
  }

  // return version
  template <bool same_version = false>
  int update_point(int old, int x, int v) {
    int ri = _update_point<same_version>(root[old], x, v, 0, n-1);
    if constexpr (same_version) {
      return old;
    } else {
      root.emplace_back(ri);
      return root.size() - 1;
    }
  }
  template <bool same_version>
  int _update_point(int old, int x, int v, int s, int e) {
    if(x < s or e < x) return old;
    int i = [&]() -> int {
      if constexpr (same_version) {
        if (old) {
          return old;
        }
      }
      data.emplace_back();
      return data.size() - 1;
    }();
    if(s == e) {
      data[i].sum = v;
    } else {
      int m = (s + e) / 2;
      data[i].left = _update_point<same_version>(data[old].left, x, v, s, m);
      data[i].right = _update_point<same_version>(data[old].right, x, v, m+1, e);
      data[i].pull(data);
    }
    return i;
  }

  ll query_range(int ver, int l, int r) {
    return _query_range(root[ver], l, r, 0, n-1);
  }
  ll _query_range(int i, int l, int r, int s, int e) {
    if(r < s or e < l or i == 0) {
      return 0;
    }
    if(l <= s and e <= r) {
      return data[i].get();
    }
    int m = (s + e) / 2;
    return _query_range(data[i].left, l, r, s, m) + _query_range(data[i].right, l, r, m+1, e);
  }
};

struct node_base {
  int left = 0, right = 0;
};

struct node : node_base {
  ll sum = 0;
  node() = default;
  auto get() const { return sum; }
  void pull(const auto& node_arr) {
    sum = node_arr[left].sum + node_arr[right].sum;
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  persistent_segment_tree<node> st(a);

  int m;
  cin >> m;
  for(int i=0, last=0; i<m; i++) {
    int t;
    cin >> t;
    if(t == 1) {
      int x, v;
      cin >> x >> v;
      last = st.update_point(last, x, v);
    } else {
      int k, l, r;
      cin >> k >> l >> r;
      cout << st.query_range(k, l, r) << nl;
    }
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
