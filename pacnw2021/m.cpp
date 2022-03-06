#include <bits/stdc++.h>
using namespace std;

#include "../../lca/tree/lca_binary_jumping.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<vector<int>> adj(n+1);
    for(int i=1; i<n; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    lca_binary_jumping lca(move(adj), 1);

    bool ok = true;
    vector<int> a(n);
    for(int i=0; i<n; i++) {
      cin >> a[i];
      if(i > 0) {
        ok &= (lca.distance(a[i], a[i-1]) <= 3);
      }
    }
    cout << ok << nl;
  }

  return 0;
}
