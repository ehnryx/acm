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
  int m, n, q;
  cin >> m >> n >> q;
  vector<pair<int, int>> parent;
  for(int i=0; i<n; i++) {
    char t;
    int a, b, c;
    cin >> t >> a >> b >> c;
    if(int s = max({a, b, c}); s >= size(parent)) {
      parent.resize(s + 1);
    }
    if(t == 'S') {
      parent[b] = pair(a, -1);
      parent[c] = pair(a, -2);
    } else {
      parent[c] = pair(a, b);
    }
  }

  vector<vector<int>> adj(size(parent));
  vector<int> degree(size(parent));
  for(int i=2; i<size(parent); i++) {
    adj[parent[i].first].push_back(i);
    degree[i]++;
    if(parent[i].second > 0) {
      adj[parent[i].second].push_back(i);
      degree[i]++;
    }
  }

  vector<int> sz(size(parent));
  queue<int> bfs;
  bfs.push(1);
  sz[1] = m;
  while(!empty(bfs)) {
    int u = bfs.front();
    bfs.pop();
    for(int v : adj[u]) {
      if(--degree[v] == 0) {
        bfs.push(v);
        sz[v] = [&] {
          if(parent[v].second == -1) {
            return (sz[parent[v].first] + 1) / 2;
          } else if(parent[v].second == -2) {
            return sz[parent[v].first] / 2;
          } else {
            return sz[parent[v].first] + sz[parent[v].second];
          }
        }();
      }
    }
  }

  while(q--) {
    int v, k;
    cin >> v >> k;
    //cerr << "QUERY " << v << " " << k << nl;

    if(k > sz[v]) {
      cout << "none" << nl;
      continue;
    }

    while(v != 1) {
      auto [a, b] = parent[v];
      if(b == -1) {
        v = a;
        k = 2*k - 1;
      } else if(b == -2) {
        v = a;
        k = 2*k;
      } else {
        int alt = min(sz[a], sz[b]);
        if(k <= alt * 2) {
          if(k % 2 == 1) {
            v = a;
            k = k/2 + 1;
          } else {
            v = b;
            k = k/2;
          }
        } else {
          v = (sz[a] > sz[b] ? a : b);
          k = k - alt;
        }
      }
      //cerr << "      " << v << " " << k << nl;
    }

    assert(k <= m);
    cout << k << nl;
  }
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
