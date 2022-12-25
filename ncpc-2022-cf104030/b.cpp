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
  vector<vector<int>> adj(n+1);
  vector<int> deg(n+1);
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    deg[a]++;
    deg[b]++;
  }

  int root = 0;
  int parent = 0;
  for(int i=1; i<=n; i++) {
    if(deg[i] == 1 or deg[i] + 1 == n) {
      continue;
    }
    root = i;
    for(int v : adj[i]) {
      if(deg[v] != 1) {
        parent = v;
      }
    }
    break;
  }
  if(root == 0) {
    return void(cout << "NO" << nl);
  }

  vector<int> res;
  auto solve = [&](auto&& self, int u, int p) -> void {
    res.push_back(u);
    for(int v : adj[u]) {
      if(v == p) continue;
      self(self, v, u);
    }
  };
  solve(solve, root, parent);
  solve(solve, parent, root);

  cout << "YES" << nl;
  for(int v : res) {
    cout << v << " ";
  }
  cout << nl;
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
