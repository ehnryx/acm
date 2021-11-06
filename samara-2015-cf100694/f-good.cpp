#include <bits/stdc++.h>
using namespace std;

#include "../../lca/graph/dinic.h"

const char nl = '\n';

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  vector<int> prod(n);
  for (int i=0; i<n; i++) {
    cin >> prod[i];
  }

  vector<string> name(n);
  for (int i=0; i<n; i++) {
    cin >> name[i];
  }

  vector<string> grid(n);
  for (int i=0; i<n; i++) {
    cin >> grid[i];
  }

  int best = -1;
  tuple<int, int, int> ans;

  for (int i=0; i<n; i++) {
    for (int j=0; j<i; j++) {
      for (int k=0; k<j; k++) {
        vector<int> cnt(8);
        for(int r=0; r<m; r++) {
          int mask = (grid[i][r] - '0') << 2 | (grid[j][r] - '0') << 1 | (grid[k][r] - '0');
          cnt[mask] += 1;
        }

        dinic<int> graph(n + 8 + 2);
        const int source = n + 8;
        const int sink = n + 8 + 1;
        for(int r=1; r<8; r++) {
          if(r & 0b100) graph.add_edge(i, n+r, cnt[r]);
          if(r & 0b010) graph.add_edge(j, n+r, cnt[r]);
          if(r & 0b001) graph.add_edge(k, n+r, cnt[r]);
          graph.add_edge(n+r, sink, cnt[r]);
        }
        graph.add_edge(source, i, prod[i]);
        graph.add_edge(source, j, prod[j]);
        graph.add_edge(source, k, prod[k]);

        int flow = graph.flow(source, sink);
        if (flow > best) {
          best = flow;
          ans = tuple(i, j, k);
        }
      }
    }
  }

  cout << best << nl;
  cout << name[get<0>(ans)] << " " << name[get<1>(ans)] << " " << name[get<2>(ans)] << nl;

  return 0;
}
