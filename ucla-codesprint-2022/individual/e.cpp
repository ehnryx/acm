#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "string/hash_polynomial.h"
%:include "string/hash_multi.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using H = hash_multi<hash_polynomial,
      (int)1e9+123, 1789,
      (int)1e9+321, 101>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  auto s = cin.read<string>(n);
  vector<H> hs;
  for(int i=0; i<n; i++) {
    hs.emplace_back(s[i]);
  }

  vector adj(n, vector<int>(n));
  vector<int> degree(n);
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(i == j) continue;
      for(int len = 1; len <= min(s[i].size(), s[j].size()); len++) {
        if(hs[i].get(s[i].size() - len, len) == hs[j].get(0, len)) {
          adj[i][j] = len;
        }
      }
      if(adj[i][j]) {
        degree[j]++;
      }
    }
  }

  vector<int> dist(n, -1);
  queue<int> bfs;
  for(int i=0; i<n; i++) {
    if(degree[i] == 0) {
      dist[i] = 0;
      bfs.push(i);
    }
  }
  int visited = 0;
  while(!empty(bfs)) {
    int u = bfs.front();
    bfs.pop();
    visited++;
    for(int v=0; v<n; v++) {
      if(!adj[u][v]) continue;
      dist[v] = max(dist[v], dist[u] + adj[u][v]);
      if(--degree[v] == 0) {
        bfs.push(v);
      }
    }
  }

  if(visited < n) {
    cout << "Shakespeare, who?" << nl;
  } else {
    cout << *max_element(begin(dist), end(dist)) << nl;
  }

  return 0;
}
