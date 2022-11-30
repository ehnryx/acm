#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/graph_list.h"
%:include "graph/dijkstra.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  GraphList<ll> g(a[0]);
  for(int i=0; i<a[0]; i++) {
    for(int j=1; j<n; j++) {
      int to = (i + a[j]) % a[0];
      g.add_arc(i, to, a[j]);
    }
  }
  auto d = dijkstra(g, 1ll<<60).run(0).get_dists();

  for(int i=0; i<m; i++) {
    ll b;
    cin >> b;
    cout << (d[b % a[0]] <= b) << " ";
  }
  cout << nl;
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
