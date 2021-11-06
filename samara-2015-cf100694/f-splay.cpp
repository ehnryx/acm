#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2")

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/splay_tree.h"
#include "../../lca/graph/dinic.h"

const char nl = '\n';

  const int N = 1e3 + 50 + 10;
  const int M = N*N;


struct Team {
  int i, j, k;
  int cnt;
  Team(): i(-1), j(-1), k(-1), cnt(-1) {}
  Team(int i, int j, int k, int cnt):
    i(i), j(j), k(k), cnt(cnt) {}
  bool operator > (const Team& v) const {
    return cnt > v.cnt;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  splay_tree<splay_node<void, int>> prod(n);
  for (int i=0; i<n; i++) {
    cin >> prod[i];
  }

  splay_tree<splay_node<void, string>> name(n); // ... pls
  for (int i=0; i<n; i++) {
    cin >> name[i];
  }

  splay_tree<splay_node<void, string>> grid(n);
  for (int i=0; i<n; i++) {
    cin >> grid[i];
  }

  vector<Team> team;
  for (int i=0; i<n; i++) {
    for (int j=0; j<i; j++) {
      for (int k=0; k<j; k++) {
        int cnt = 0;
        for (int r=0; r<m; r++) {
          cnt += grid[i][r] == '1' || grid[j][r] == '1' || grid[k][r] == '1';
        }
        team.push_back(Team(k, j, i, cnt));
      }
    }
  }
  sort(team.begin(), team.end(), greater<Team>());

  int best = -1;
  Team ans;

  for (const Team& t : team) {
    if (clock() > 1.789*CLOCKS_PER_SEC) break;

    dinic<int> graph(n + m + 2);
    const int source = n + m;
    const int sink = n + m + 1;
    for (int i=0; i<m; i++) {
      graph.add_edge(n+i, sink, 1);
      if (grid[t.i][i] == '1') graph.add_edge(t.i, n+i, 1);
      if (grid[t.j][i] == '1') graph.add_edge(t.j, n+i, 1);
      if (grid[t.k][i] == '1') graph.add_edge(t.k, n+i, 1);
    }
    graph.add_edge(source, t.i, prod[t.i]);
    graph.add_edge(source, t.j, prod[t.j]);
    graph.add_edge(source, t.k, prod[t.k]);

    int flow = graph.flow(source, sink);
    if (flow > best) {
      best = flow;
      ans = t;
    }
  }

  assert(ans.cnt != -1);

  cout << best << nl;
  cout << name[ans.i] << " " << name[ans.j] << " " << name[ans.k] << nl;

  return 0;
}
