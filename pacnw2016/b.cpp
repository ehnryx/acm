#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

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
  vector g(n+2, vector(m+2, '#'));
  pair<int, int> start, end;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
      if(g[i][j] == 'R') {
        start = pair(i, j);
      } else if(g[i][j] == 'E') {
        end = pair(i, j);
      }
    }
  }
  string s;
  cin >> s;

  auto follow = [](int i, int j, char c) {
    switch(c) {
      case 'U': return pair(i-1, j);
      case 'D': return pair(i+1, j);
      case 'L': return pair(i, j-1);
      case 'R': return pair(i, j+1);
    }
    assert(false);
  };

  vector dist(n+1, vector(m+1, vector(size(s) + 1, -1)));
  deque<tuple<int, int, int, int>> bfs;
  bfs.emplace_back(start.first, start.second, 0, 0);
  while(not empty(bfs)) {
    auto [i, j, k, d] = bfs.front();
    bfs.pop_front();
    if(g[i][j] == 'E') {
      return void(cout << d << nl);
    }
    if(dist[i][j][k] != -1) continue;
    dist[i][j][k] = d;
    // follow
    if(k < size(s)) {
      auto [ni, nj] = follow(i, j, s[k]);
      if(g[ni][nj] == '#') {
        bfs.emplace_front(i, j, k+1, d);
      } else {
        bfs.emplace_front(ni, nj, k+1, d);
      }
    }
    // delete
    if(k < size(s)) {
      bfs.emplace_back(i, j, k+1, d+1);
    }
    // insert
    for(char c : { 'L', 'R', 'U', 'D' }) {
      auto [ni, nj] = follow(i, j, c);
      if(g[ni][nj] != '#') {
        bfs.emplace_back(ni, nj, k, d+1);
      }
    }
  }

  assert(false);
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
