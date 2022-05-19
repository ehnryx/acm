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

const int M = 121;
int bfs[M][M];
ll ans[M][M][2];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  while(T--) {
    int n, m, stn;
    cin >> n >> m >> stn;
    int tank;
    cin >> tank;
    graph_list<int> graph(n+1);
    for(int i=0; i<m; i++) {
      int a, b, c;
      cin >> a >> b >> c;
      graph.add_edge(a, b, c);
    }
    vector<int> at(stn), cost(stn);
    for(int i=0; i<stn; i++) {
      cin >> at[i] >> cost[i];
    }
    int s, t;
    cin >> s >> t;
    at.push_back(t);
    s = find(begin(at), end(at), s) - begin(at);
    t = stn;

    for(int i=0; i<stn; i++) {
      auto dists = dijkstra(graph, at[i], -1).get_dists();
      for(int j=0; j<=stn; j++) {
        bfs[i][j] = dists[at[j]];
      }
    }

    // at i, from j
    memset(ans, 0x3f, sizeof ans);
    ans[s][s][0] = 0;
    queue<tuple<int, int, int>> todo;
    todo.emplace(s, s, 0);
    while(!empty(todo)) {
      auto [i, j, f] = todo.front();
      todo.pop();
      int leftover = tank - bfs[j][i];

#define PUSH(F) \
      if(cur < ans[k][i][F]) { \
        ans[k][i][F] = cur; \
        todo.emplace(k, i, F); \
      }

      if(f) {
        for(int k=0; k<=stn; k++) {
          if(bfs[i][k] == -1 || bfs[i][k] > tank) continue;
          // empty
          if(leftover < bfs[i][k]) {
            ll cur = ans[i][j][f] + (bfs[i][k] - leftover) * (ll)cost[i];
            PUSH(0);
          }
          // full
          {
            ll cur = ans[i][j][f] + (tank - leftover) * (ll)cost[i];
            PUSH(1);
          }
        }
      } else {
        for(int k=0; k<=stn; k++) {
          if(bfs[i][k] == -1 || bfs[i][k] > tank) continue;
          // empty
          {
            ll cur = ans[i][j][f] + bfs[i][k] * (ll)cost[i];
            PUSH(0);
          }
          // full
          {
            ll cur = ans[i][j][f] + tank * (ll)cost[i];
            PUSH(1);
          }
        }
      }
    }

    ll best = ans[t][t][0];
    for(int i=0; i<stn; i++) {
      best = min(best, ans[t][i][0]);
    }
    cout << best << nl;
  }

  return 0;
}
