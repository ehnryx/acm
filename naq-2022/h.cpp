#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/dinic.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, l, r;
  cin >> n >> l >> r;
  vector<int> x(n);
  for(int i=0; i<n; i++) {
    cin >> x[i];
  }
  sort(begin(x), end(x));

  vector<int> d(n+1);
  for(int i=1; i<n; i++) {
    if(x[i] - x[i-1] < l) {
      return void(cout << -1 << nl);
    }
    d[i] = 2 * (x[i] - x[i-1] - l);
  }
  d[0] = d[n] = 2*r;

  dinic<ll> graph(n + 3);
  const int source = n + 1;
  const int sink = source + 1;
  for(int i=0; i<=n; i++) {
    if(i % 2 == 0) {
      graph.add_edge(source, i, d[i]);
      if(i > 0) {
        graph.add_edge(i, i-1, r - l);
      }
      if(i+1 <= n) {
        graph.add_edge(i, i+1, r - l);
      }
    } else {
      graph.add_edge(i, sink, d[i]);
    }
  }
  cout << graph.flow(source, sink) + (ll)n * l << nl;
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
