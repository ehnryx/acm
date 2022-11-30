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


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n1, n2, m, q;
  cin >> n1 >> n2 >> m >> q;

  map<pair<int, int>, int> edges;
  dinic<int> graph(n1 + n2 + 2);
  const int source = 0;
  const int sink = n1 + n2 + 1;

  for(int i=1; i<=n1; i++) {
    graph.add_edge(source, i);
  }
  for(int i=1; i<=n2; i++) {
    graph.add_edge(i + n1, sink);
  }

  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    edges[pair(a, b)] = i + 1;
    graph.add_edge(a, b + n1);
  }
  graph.flow(source, sink);

  ll sum = 0;

  vector<int> cut;
  set<pair<int, int>> have;
  for(int i=1; i<=n1; i++) {
    if(!graph.left_of_min_cut(i)) {
      cut.push_back(i);
      for(const auto& e : graph.adj[i]) {
        if(e.flow && e.to > i) {
          have.emplace(i, e.to - n1);
          sum += edges[pair(i, e.to - n1)];
        }
      }
    }
  }
  for(int i=1; i<=n2; i++) {
    if(graph.left_of_min_cut(i + n1)) {
      cut.push_back(i + n1);
      for(const auto& e : graph.adj[i + n1]) {
        if(e.flow && e.to < i + n1) {
          have.emplace(e.to, i);
          sum += edges[pair(e.to, i)];
        }
      }
    }
  }

  while(q--) {
    int t;
    cin >> t;
    if(t == 1) {
      cout << 1 << nl;
      if (cut.back() <= n1) {
        cout << cut.back() << nl;
      } else {
        cout << -(cut.back() - n1) << nl;
      }
      for(const auto& e : graph.adj[cut.back()]) {
        if(e.flow && (e.to < cut.back()) == (cut.back() > n1)) {
          int l = min(cut.back(), e.to);
          int r = max(cut.back(), e.to);
          assert(have.erase(pair(l, r - n1)));
          sum -= edges[pair(l, r - n1)];
        }
      }
      cut.pop_back();
      cout << sum << nl;
    } else {
      cout << size(have) << nl;
      for(auto it : have) {
        cout << edges[it] << " ";
      }
      cout << nl;
    }
    cout.flush();
  }

  return 0;
}
