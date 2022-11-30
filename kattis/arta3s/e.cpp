#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/dijkstra.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m, k1, k2;
  cin >> n >> m >> k1 >> k2;
  auto get = [=](int u, int a, int b) {
    return (u-1) * (k1+1) * (k2+1) + a * (k2+1) + b;
  };
  vector_graph<ll> g(n * (k1+1) * (k2+2));
  for(int i=0; i<m; i++) {
    int a, b, c, t;
    cin >> a >> b >> c >> t;
    if(t == 1) {
      for(int ii=0; ii<k1; ii++) {
        for(int jj=0; jj<=k2; jj++) {
          g.add_arc(get(a, ii, jj), get(b, ii+1, jj), c);
          g.add_arc(get(b, ii, jj), get(a, ii+1, jj), c);
        }
      }
    } else if(t == 2) {
      for(int ii=0; ii<=k1; ii++) {
        for(int jj=0; jj<k2; jj++) {
          g.add_arc(get(a, ii, jj), get(b, ii, jj+1), c);
          g.add_arc(get(b, ii, jj), get(a, ii, jj+1), c);
        }
      }
    } else {
      for(int ii=0; ii<=k1; ii++) {
        for(int jj=0; jj<=k2; jj++) {
          g.add_arc(get(a, ii, jj), get(b, ii, jj), c);
          g.add_arc(get(b, ii, jj), get(a, ii, jj), c);
        }
      }
    }
  }
  int s, t;
  cin >> s >> t;
  auto ans = dijkstra(g, -1ll).run(get(s, 0, 0)).dist[get(t, k1, k2)];
  cout << ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
