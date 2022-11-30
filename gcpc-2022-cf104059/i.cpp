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


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<int> cost(n+1);
  vector<vector<int>> value(n);
  for(int i=0; i<n; i++) {
    cin >> cost[i];
    value[i].resize(min(m, n-i));
    //cerr << "SIZE " << i << " " << size(value[i]) << nl;
    for(int j=0; j<size(value[i]); j++) {
      cin >> value[i][j];
    }
  }
  cost[n] = 0;

  vector<vector<pair<int, int>>> adj(n+1);
  vector<int> deg(n+1);
  for(int i=0; i<n; i++) {
    for(int j=0; j<size(value[i]); j++) {
      adj[i].emplace_back(i + j+1, cost[i + j+1] - value[i][j]);
      deg[i + j+1]++;
    }
  }

  vector<ll> ans(n+1, numeric_limits<ll>::max());
  queue<int> bfs;
  bfs.push(0);
  ans[0] = cost[0];
  while(not empty(bfs)) {
    int u = bfs.front();
    bfs.pop();
    for(auto [v, c] : adj[u]) {
      ans[v] = min(ans[v], ans[u] + c);
      if(--deg[v] == 0) {
        bfs.push(v);
      }
    }
  }
  cout << ans[n] << nl;
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
