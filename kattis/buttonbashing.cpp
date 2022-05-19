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

  const int m = 3600;

  int T;
  cin >> T;
  while(T--) {
    int n, goal;
    cin >> n >> goal;
    graph_list<void> g(m + 1);
    auto ds = cin.read<int>(n);
    for(int i=0; i<g.size(); i++) {
      for(int d : ds) {
        // read the problem statement
        g.add_arc(i, clamp(i+d, 0, m));
      }
    }
    auto dist = breadth_first(g, 0).dist;
    int small = numeric_limits<int>::max();
    int diff = numeric_limits<int>::max();
    for(int i=goal; i<g.size(); i++) {
      if(dist[i] != -1) {
        small = min(small, dist[i]);
        diff = min(diff, i - goal);
        break; // read the problem statement
      }
    }
    cout << small << " " << diff << nl;
  }

  return 0;
}
