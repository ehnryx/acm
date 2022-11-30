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
  int n;
  cin >> n;
  vector<int> a(n+1);
  vector<int> root(n+1);
  vector<unordered_set<int>> start(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    if(i + a[i] < 1 || n < i + a[i]) {
      root[i] = i;
      start[i].insert(a[i]);
    }
  }

  vector<bool> vis(n+1);
  for(int i=1; i<=n; i++) {
    if(vis[i]) continue;
    vector<int> path;
    int at = i;
    while(1<=at && at<=n && !vis[at]) {
      vis[at] = true;
      path.push_back(at);
      at += a[at];
    }
    if(1 <= at && at <= n) {
      reverse(begin(path), end(path));
      int len = (int)distance(begin(path), find(begin(path), end(path), at)) + 1;
      if(len <= path.size()) {
        for(int j=0; j<len; j++) {
          root[path[j]] = path.front();
          start[path.front()].insert(a[path[j]]);
        }
      }
    }
  }

  vector<vector<int>> adj(n+1);
  for(int i=1; i<=n; i++) {
    if(root[i]) continue;
    adj[i + a[i]].push_back(i);
  }

  ll ans = 0;

  auto solve = [&](auto&& self, int u, int r) -> void {
    bool rem = start[r].insert(a[u]).second;
    for(int v : adj[u]) {
      self(self, v, r);
    }
    ans += size(start[r]);
    if(rem) {
      start[r].erase(a[u]);
    }
  };

  for(int i=1; i<=n; i++) {
    if(root[i]) {
      solve(solve, i, root[i]);
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
