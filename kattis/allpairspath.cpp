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
  for(int n, m, q; cin >> n >> m >> q && n; ) {
    static constexpr int big = numeric_limits<int>::max() / 2;
    static constexpr int small = numeric_limits<int>::min() / 2;
    vector adj(n, vector<int>(n, big));
    for(int i=0; i<n; i++) {
      adj[i][i] = 0;
    }
    for(int i=0; i<m; i++) {
      int a, b, c;
      cin >> a >> b >> c;
      adj[a][b] = min(adj[a][b], c);
    }

    for(int k=0; k<n; k++) {
      for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
          if(adj[i][k] == big || adj[k][j] == big) continue;
          adj[i][j] = max(small, min(adj[i][j], adj[i][k] + adj[k][j]));
        }
      }
    }

    auto neg = adj;
    for(int k=0; k<n; k++) {
      for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
          if(neg[i][k] == big || adj[k][j] == big) continue;
          neg[i][j] = max(small, min(neg[i][j], neg[i][k] + neg[k][j]));
        }
      }
    }

    while(q--) {
      int a, b;
      cin >> a >> b;
      if(adj[a][b] == big) {
        cout << "Impossible" << nl;
      } else if(adj[a][b] == small || adj[a][b] != neg[a][b]) {
        cout << "-Infinity" << nl;
      } else {
        cout << adj[a][b] << nl;
      }
    }

    cout << nl;
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
