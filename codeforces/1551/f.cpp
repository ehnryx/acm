%:include <bits/stdc++.h>
using namespace std;

#include "../../../lca/misc/fast_input.h"
#include "../../../lca/number/mod_int.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  fast_input cin;

  const int M = 100 + 1;
  vector ncr(M, vector<Int>(M));
  for(int i=0; i<M; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
  }

  int T;
  cin >> T;
  while(T--) {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n+1);
    for(int i=1; i<n; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    if(k == 2) [[unlikely]] {
      cout << n * (n-1) / 2 << nl;
      continue;
    }

    Int ans = 0;
    for(int s=1; s<=n; s++) {
      vector<int> dist(n+1, -1);
      vector<vector<int>> df(n);
      dist[s] = 0;
      for(int t : adj[s]) {
        vector<int> df_cur(n);
        queue<int> bfs;
        bfs.push(t);
        dist[t] = 1;
        while(!empty(bfs)) {
          int u = bfs.front();
          bfs.pop();
          df_cur[dist[u]]++;
          for(int v : adj[u]) {
            if(dist[v] == -1) [[likely]] {
              dist[v] = dist[u] + 1;
              bfs.push(v);
            }
          }
        }
        for(int i=1; i<n; i++) {
          if(df_cur[i]) {
            df[i].push_back(df_cur[i]);
          }
        }
      }
      for(int i=1; i<n; i++) {
        vector<Int> dp(k+1);
        dp[0] = 1;
        for(int v : df[i]) {
          for(int j=k; j>0; j--) {
            dp[j] += dp[j-1] * v;
          }
        }
        ans += dp[k];
      }
    }
    cout << ans << nl;
  }

  return 0;
}
