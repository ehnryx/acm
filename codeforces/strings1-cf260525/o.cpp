#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "string/suffix_tree.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<string> s(n);
  vector<int> all, stop;
  for(int i=0; i<n; i++) {
    cin >> s[i];
    all.resize(size(all) + size(s[i]) + 1);
    transform(begin(s[i]), end(s[i]), all.end() - size(s[i]) - 1,
        [n](char c) { return (int)c + n + 1; });
    all.back() = i + 1;
    stop.resize(size(stop) + size(s[i]) + 1, size(stop) + size(s[i]));
  }
  suffix_tree st(all);
  vector<int> cost(n), cost_at;
  for(int i=0; i<n; i++) {
    cin >> cost[i];
    cost_at.resize(size(cost_at) + size(s[i]) + 1, cost[i]);
  }

  ll ans = 0;
  auto solve = [&](auto&& self, int u) -> ll {
    ll val = 0;
    if(stop[st[u].left] < st[u].right) {
      val += cost_at[stop[st[u].left]];
      if(stop[st[u].left] > st[u].left) {
        ans = max(ans, (st.depth(u) + stop[st[u].left] - st[u].left) * val);
      }
    } else {
      for(auto [c, v] : st[u]) {
        val += self(self, v);
      }
      ans = max(ans, (st.depth(u) + st.length(u)) * val);
    }
    return val;
  };

  solve(solve, st.root());
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
