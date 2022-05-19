#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

%:include "graph/graph_builder.h"
%:include "graph/min_span_forest.h"

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
  vector<int> val(n);
  for(int i=0; i<n; i++) {
    cin >> val[i];
  }
  graph_list<void> g(n);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
  }

  auto dsu = *min_span_forest(g);
  for(int i=0; i<n; i++) {
    if(i != dsu[i]) {
      val[dsu[i]] += val[i];
    }
  }
  bool ok = true;
  for(int i=0; i<n; i++) {
    if(i == dsu[i]) {
      ok &= (val[i] == 0);
    }
  }
  cout << (ok ? "POSSIBLE" : "IMPOSSIBLE") << nl;

  return 0;
}
