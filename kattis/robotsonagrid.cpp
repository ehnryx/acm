#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "number/mod_int.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr ll MOD = (1ll<<31) - 1;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector g(n+2, vector(n+2, char('#')));
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      cin >> g[i][j];
    }
  }

  vector dp(n+2, vector(n+2, Int(0ll)));
  dp[1][1] = 1ll;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      if(g[i][j] == '#') continue;
      if(g[i-1][j] != '#') dp[i][j] += dp[i-1][j];
      if(g[i][j-1] != '#') dp[i][j] += dp[i][j-1];
    }
  }
  if(dp[n][n].value()) {
    return void(cout << dp[n][n].value() << nl);
  }

  queue<pair<int, int>> bfs;
  vector vis(n+2, vector(n+2, false));
  static_assert(is_same_v<decltype(vis), vector<vector<bool>>>);
  bfs.emplace(1, 1);
  vis[1][1] = true;
  while(not empty(bfs)) {
    auto [i, j] = bfs.front();
    bfs.pop();
    for(auto [di, dj] : {
        pair(1, 0), pair(0, 1), pair(-1, 0), pair(0, -1) }) {
      int ni = i + di;
      int nj = j + dj;
      if(g[ni][nj] == '#' or vis[ni][nj]) continue;
      vis[ni][nj] = true;
      bfs.emplace(ni, nj);
    }
  }
  if(vis[n][n]) {
    cout << "THE GAME IS A LIE" << nl;
  } else {
    cout << "INCONCEIVABLE" << nl;
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
