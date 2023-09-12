#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "utility/nd_array.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  nd_array<int, 2> g(n+2, n+2, -1);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      cin >> g(i, j);
    }
  }
  nd_array<vector<pair<int, int>>, 2> adj(n+2, n+2);
  nd_array<int, 2> deg(n+2, n+2);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      for(auto [ni, nj] : {
          pair(i+1, j), pair(i-1, j), pair(i, j+1), pair(i, j-1) }) {
        if(g(i, j) > g(ni, nj)) {
          adj(ni, nj).emplace_back(i, j);
          deg(i, j)++;
        }
      }
    }
  }

  queue<pair<int, int>> bfs;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      if(deg(i, j) == 0) {
        bfs.emplace(i, j);
      }
    }
  }
  while(not empty(bfs)) {
    auto [i, j] = bfs.front();
    bfs.pop();
    for(auto [ni, nj] : adj(i, j)) {
      if(--deg(ni, nj) == 0) {
        bfs.emplace(ni, nj);
      }
    }
  }

  m++;
  nd_array<int, 3> dp(n+2, n+2, m+1, numeric_limits<int>::min());
  for(int i=0; i<=n+1; i++) {
    for(int j=0; j<=n+1; j++) {
      if(deg(i, j) == 0 and g(i, j) == -1) {
        bfs.emplace(i, j);
        for(int f=0; f<=m; f++) {
          dp(i, j, f) = 0;
        }
      }
    }
  }
  while(not empty(bfs)) {
    auto [i, j] = bfs.front();
    bfs.pop();
    for(auto [ni, nj] : adj(i, j)) {
      for(int f=1; f<=m; f++) {
        dp(ni, nj, f) = max(dp(ni, nj, f), dp(i, j, f-1) + g(ni, nj));
      }
      if(--deg(ni, nj) == 0) {
        bfs.emplace(ni, nj);
      }
    }
  }

  int ans = 0;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      ans = max(ans, dp(i, j, m));
    }
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
