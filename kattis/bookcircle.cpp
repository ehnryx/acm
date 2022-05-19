#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
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

  dinic<int> g(n + m + 2);
  int source = n + m;
  int sink = source + 1;

  unordered_map<string, pair<int, int>> edges;

  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    int k;
    cin >> k;
    while(k--) {
      cin >> s;
      edges[s].first = i;
    }
    g.add_edge(source, i);
  }

  for(int i=0; i<m; i++) {
    string s;
    cin >> s;
    int k;
    cin >> k;
    while(k--) {
      cin >> s;
      edges[s].second = n + i;
    }
    g.add_edge(n + i, sink);
  }

  for(const auto& [_, e] : edges) {
    g.add_edge(e.first, e.second);
  }

  cout << g.flow(source, sink) << nl;

  return 0;
}
