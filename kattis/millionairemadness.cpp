#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "graph/graph.h"
%:include "graph/dijkstra.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct Int {
  int v;
  Int(int _v=0): v(_v) {}
  int value() const { return v; }
  Int operator + (const Int& o) const { return Int(max(v, o.v)); }
  bool operator != (const Int& o) const { return v != o.v; }
  bool operator <= (const Int& o) const { return v <= o.v; }
  bool operator > (const Int& o) const { return v > o.v; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  auto h = cin.read<int>(n, m);

  function<int(int, int)> get = [n,m](int i, int j) {
    return i*m + j;
  };

  graph_list<Int> g(n * m);
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      if(i) {
        g.add_arc(get(i-1, j), get(i, j), max(0, h[i][j] - h[i-1][j]));
        g.add_arc(get(i, j), get(i-1, j), max(0, h[i-1][j] - h[i][j]));
      }
      if(j) {
        g.add_arc(get(i, j-1), get(i, j), max(0, h[i][j] - h[i][j-1]));
        g.add_arc(get(i, j), get(i, j-1), max(0, h[i][j-1] - h[i][j]));
      }
    }
  }
  cout << dijkstra(g, get(0, 0), 1 << 30).dist[get(n-1, m-1)].value() << nl;

  return 0;
}
