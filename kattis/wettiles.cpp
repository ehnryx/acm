#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "graph/graph.h"
%:include "graph/breadth_first.h"

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

  for(int x, y, t, n, m; cin >> x >> y >> t >> n >> m && x != -1; ) {
    function<int(int, int)> get = [x, y](int i, int j) {
      return i*y + j;
    };

    graph_list<void> g(x*y+1);
    const int source = x*y;
    for(int i=0; i<n; i++) {
      int a, b;
      cin >> a >> b;
      g.add_arc(source, get(a - 1, b - 1));
    }

    vector dead(x, vector<bool>(y));
    for(int i=0; i<m; i++) {
      int a, b, c, d;
      cin >> a >> b >> c >> d;
      int len = max(abs(a - c), abs(b - d));
      int dac = (a == c ? 0 : (c - a) / abs(c - a));
      int dbd = (b == d ? 0 : (d - b) / abs(d - b));
      for(int j=0; j<=len; j++) {
        dead[a + j*dac - 1][b + j*dbd - 1] = true;
      }
    }

    for(int i=0; i<x; i++) {
      for(int j=0; j<y; j++) {
        if(dead[i][j]) continue;
        if(i && !dead[i-1][j]) {
          g.add_edge(get(i, j), get(i-1, j));
        }
        if(j && !dead[i][j-1]) {
          g.add_edge(get(i, j), get(i, j-1));
        }
      }
    }

    int ans = 0;
    for(int d : breadth_first(g, source).dist) {
      ans += (d != -1 && d <= t);
    }
    cout << ans - 1 << nl;
  }

  return 0;
}
