#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "ds/union_find.h"
%:include "utility/nd_array.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct ufo {
  vector<int>& ans;
  unordered_set<int> q;
  ufo(vector<int>& v): ans(v) {}
  static void swap_args(...) {}
  void merge(ufo& o, int height) {
    for(int i : o.q) {
      if(auto [it, ok] = q.insert(i); not ok) {
        q.erase(it);
        ans[i] = height;
      }
    }
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m, q;
  cin >> n >> m >> q;
  nd_array<int, 2> g(n+2, m+2);
  vector<tuple<int, int, int>> ev;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g(i, j);
      ev.emplace_back(g(i, j), i, j);
    }
  }
  sort(begin(ev), end(ev));

  // bool doesn't work because vector<bool>
  nd_array<char, 2> have(n+2, m+2, false);
  vector<int> ans(q);
  union_find<ufo> dsu(have.size(), ufo(ans));
  for(int i=0; i<q; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    if(tie(a, b) == tie(x, y)) {
      ans[i] = g(a, b);
    } else {
      dsu.get(have.index(a, b)).q.insert(i);
      dsu.get(have.index(x, y)).q.insert(i);
    }
  }

  for(auto [v, i, j] : ev) {
    have(i, j) = true;
    for(auto [ni, nj] : {
        pair(i-1, j), pair(i+1, j), pair(i, j-1), pair(i, j+1) }) {
      if(have(ni, nj)) {
        dsu.link(have.index(i, j), have.index(ni, nj), v);
      }
    }
  }
  for(auto v : ans) {
    cout << v << nl;
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
