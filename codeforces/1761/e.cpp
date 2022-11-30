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


#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector g(n, vector<char>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> g[i][j];
      g[i][j] = g[i][j] == '1';
    }
  }

  vector<bool> vis(n);
  vector<int> nodes(n), edges(n), root(n);
  vector<int> all;
  for(int i=0; i<n; i++) {
    if(vis[i]) continue;
    queue<int> bfs;
    bfs.push(i);
    vis[i] = true;
    while(not empty(bfs)) {
      int u = bfs.front();
      bfs.pop();
      nodes[i]++;
      root[u] = i;
      for(int j=0; j<n; j++) {
        if(g[u][j]) {
          edges[i]++;
          if(not vis[j]) {
            bfs.push(j);
            vis[j] = true;
          }
        }
      }
    }
    all.push_back(i);
  }

  if(size(all) == 1) {
    return void(cout << 0 << nl);
  }

  for(int r : all) {
    if(nodes[r] == 1 or edges[r] != nodes[r] * (nodes[r] - 1)) {
      cout << 1 << nl;
      int out = -1;
      for(int i=0; i<n; i++) {
        if(root[i] != r) continue;
        int degree = accumulate(begin(g[i]), end(g[i]), 0);
        if(degree <= 1) {
          return void(cout << i + 1 << nl);
        } else if(degree != nodes[r] - 1) {
          out = i;
        }
      }
      assert(out != -1);
      return void(cout << out + 1 << nl);
    }
  }

  if(size(all) == 2) {
    if(nodes[all[0]] > nodes[all[1]]) {
      swap(all[0], all[1]);
    }
    cout << nodes[all[0]] << nl;
    for(int i=0; i<n; i++) {
      if(root[i] == all[0]) {
        cout << i + 1 << " ";
      }
    }
    return void(cout << nl);
  }

  cout << 2 << nl;
  cout << all[0] + 1 << " " << all[1] + 1 << nl;
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
