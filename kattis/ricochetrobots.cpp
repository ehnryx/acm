#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int convert(vector<pair<int, int>> v) {
  int res = 0;
  for(int i=1; i<size(v); i++) {
    res = res * 10 + v[i].first - 1;
    res = res * 10 + v[i].second - 1;
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int k, m, n, L;
  cin >> k >> m >> n >> L;
  auto g = cin.readinit<char, 1, 1>(n, m, 'W');

  vector<pair<int, int>> at(k + 1);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(g[i][j] == 'X') {
        g[i][j] = '0';
      }
      if(isdigit(g[i][j])) {
        at[g[i][j] - '0'] = pair(i, j);
        g[i][j] = '.';
      }
    }
  }

  function<pair<int, int>(pair<int, int>, pair<int, int>, vector<pair<int, int>>)> transition =
    [&](pair<int, int> state, pair<int, int> dxy, vector<pair<int, int>> all) {
      auto [i, j] = state;
      auto [di, dj] = dxy;
      while(true) {
        int ni = i + di;
        int nj = j + dj;
        if(g[ni][nj] == 'W') break;
        if(find(begin(all) + 1, end(all), pair(ni, nj)) != end(all)) break;
        tie(i, j) = tie(ni, nj);
      }
      return pair(i, j);
    };

  queue<vector<pair<int, int>>> bfs;
  //map<vector<pair<int, int>>, int> dist;
  map<int, int> dist;

  bfs.push(at);
  dist[convert(at)] = 0;
  while(!empty(bfs)) {
    auto state = bfs.front();
    bfs.pop();
    int d = dist[convert(state)];
    for(int t=1; t<=k; t++) {
      for(auto dxy : {
          pair(0, 1), pair(1, 0), pair(0, -1), pair(-1, 0) })
      {
        auto ns = state;
        ns[t] = transition(state[t], dxy, state);
        if(ns[0] == ns[1]) {
          cout << d + 1 << nl;
          return 0;
        }
        if(int idx = convert(ns);
            d + 1 < L && !dist.count(idx)) {
          dist[idx] = d + 1;
          bfs.push(ns);
        }
      }
    }
  }

  cout << "NO SOLUTION" << nl;

  return 0;
}
