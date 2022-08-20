#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

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

  dinic<int> g(2*m + 2);
  const int source = 2*m;
  const int sink = source + 1;

  set<pair<int, int>> have;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    if(have.insert(pair(x, y)).second) {
      g.add_edge(x, m + y);
    }
  }
  for(int i=0; i<m; i++) {
    g.add_edge(source, i);
    g.add_edge(m + i, sink);
  }

  cout << g.flow(source, sink) << nl;

  return 0;
}
