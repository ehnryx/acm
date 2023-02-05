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
  vector<vector<int>> adj(n+1);
  vector<int> in(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    in[b]++;
  }

  queue<int> bfs;
  for(int i=1; i<=n; i++) {
    if(in[i] == 0) {
      bfs.push(i);
    }
  }
  vector<int> ans;
  while(not empty(bfs)) {
    int u = bfs.front();
    bfs.pop();
    ans.push_back(u);
    for(int v : adj[u]) {
      if(--in[v] == 0) {
        bfs.push(v);
      }
    }
  }

  if(size(ans) != n) {
    cout << "IMPOSSIBLE" << nl;
  } else {
    for(int i : ans) {
      cout << i << nl;
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
