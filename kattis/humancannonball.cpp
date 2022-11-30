#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "geometry/point.h"
%:include "graph/floyd_warshall.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using pt = point<double>;

double get_dist(pt s, pt t) {
  double d = abs(s - t);
  return min(d, 10 + abs(d - 50));
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  pt s, t;
  cin >> s >> t;

  int n;
  cin >> n;
  vector<pt> p(n);
  floyd_warshall<double> trivial(n + 2, -1);
  trivial.add_arc(n, n+1, abs(s - t));
  for(int i=0; i<n; i++) {
    cin >> p[i];
    trivial.add_arc(n, i, abs(s - p[i]));
    trivial.add_arc(i, n+1, get_dist(p[i], t));
    for(int j=0; j<i; j++) {
      trivial.add_edge(i, j, get_dist(p[i], p[j]));
    }
  }
  trivial.run();
  cout << trivial[n][n+1] / 5 << nl;

  return 0;
}
