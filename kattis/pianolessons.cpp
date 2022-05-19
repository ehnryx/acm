#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "graph/dinic.h"

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
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  dinic<int> g(n+m+2);
  const int source = n + m;
  const int sink = source + 1;
  for(int i=0; i<n; i++) {
    int k;
    cin >> k;
    for(int j=0; j<k; j++) {
      int v;
      cin >> v;
      g.add_edge(i, n + v - 1, 1);
    }
    g.add_edge(source, i, 1);
  }
  for(int i=0; i<m; i++) {
    g.add_edge(n + i, sink, 1);
  }
  cout << g.flow(source, sink) << nl;

  return 0;
}
