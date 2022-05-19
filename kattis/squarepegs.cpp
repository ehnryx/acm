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

  int n, m, k;
  cin >> n >> m >> k;

  const int source = n + m + k;
  const int sink = source + 1;
  dinic<int> g(sink + 1);

  vector<int> plot(n);
  for(int i=0; i<n; i++) {
    cin >> plot[i];
    g.add_edge(source, i);
  }

  for(int i=0; i<m; i++) {
    int r;
    cin >> r;
    for(int j=0; j<n; j++) {
      if(r < plot[j]) {
        g.add_edge(j, n+i);
      }
    }
    g.add_edge(n+i, sink);
  }

  for(int i=0; i<k; i++) {
    int s;
    cin >> s;
    for(int j=0; j<n; j++) {
      if(s*s < 2 * plot[j]*plot[j]) {
        g.add_edge(j, n+m+i);
      }
    }
    g.add_edge(n+m+i, sink);
  }

  cout << g.flow(source, sink) << nl;

  return 0;
}
