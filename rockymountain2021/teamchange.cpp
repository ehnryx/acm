#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/dinic.h"
%:include "graph/dinic_bipartite.h"

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
  string init;
  cin >> init;
  string goal;
  cin >> goal;

  dinic<int> g(2*n + 2);
  const int source = 0;
  const int sink = 1;
  for(int i=1; i<=n; i++) {
    if(goal[i-1] == '?') {
      g.add_edge(source, 2*i);
      g.add_edge(2*i + 1, sink);
      g.add_edge(2*i, 2*i + 1);
    } else if(init[i-1] == goal[i-1]) {
      g.add_edge(2*i + 1, sink);
    } else {
      g.add_edge(source, 2*i);
    }
  }

  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(2*a, 2*b + 1);
    g.add_edge(2*b, 2*a + 1);
  }

  g.flow(source, sink);
  vector<int> res = max_bipartite_set(g, source, sink);

  cerr << "ans: " << res.size() << nl;
  string ans(n, 'X');
  for(int it : res) {
    int i = it / 2 - 1;
    if(it % 2 == 0) {
      ans[i] = init[i] ^ 'A' ^ 'B';
    } else {
      ans[i] = init[i];
    }
  }
  cout << ans << nl;

  return 0;
}
