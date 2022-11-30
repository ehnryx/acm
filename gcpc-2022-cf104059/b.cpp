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


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  static constexpr int M = 2e7;
  vector<bool> prime(M, true);
  prime[0] = prime[1] = false;
  for(int i=2; i*i<M; i++) {
    if(prime[i]) {
      for(int j=i*i; j<M; j+=i) {
        prime[j] = false;
      }
    }
  }

  int n;
  cin >> n;
  bool one = false;
  vector<int> all, other;
  for(int i=0; i<n; i++) {
    int v;
    cin >> v;
    if(v == 1) {
      one = true;
    } else {
      all.push_back(v);
      if(not prime[v + 1]) {
        other.push_back(v);
      }
    }
  }

  auto solve = [&prime](const vector<int>& a) {
    if(empty(a)) {
      return 0;
    }

    //cerr << "SOLVE " << a << nl;
    vector<vector<int>> adj(size(a));
    for(int i=0; i<size(a); i++) {
      for(int j=0; j<i; j++) {
        if(prime[a[i] + a[j]]) {
          adj[i].push_back(j);
          adj[j].push_back(i);
        }
      }
    }

    vector<int> dist(size(a), -1);
    for(int i=0; i<size(a); i++) {
      if(dist[i] != -1) continue;
      queue<int> bfs;
      dist[i] = 0;
      bfs.push(i);
      while(not empty(bfs)) {
        int u = bfs.front();
        bfs.pop();
        for(int v : adj[u]) {
          if(dist[v] == -1) {
            dist[v] = dist[u] + 1;
            bfs.push(v);
          } else {
            assert(dist[v] % 2 != dist[u] % 2);
          }
        }
      }
    }

    dinic<int> g(size(a) + 2);
    const int source = size(a);
    const int sink = source + 1;
    for(int i=0; i<size(a); i++) {
      if(dist[i] % 2 == 0) {
        //cerr << "ADD S -> " << a[i] << nl;
        g.add_edge(source, i);
        for(int v : adj[i]) {
          g.add_edge(i, v);
          //cerr << "ADD " << a[i] << " -> " << a[v] << nl;
        }
      } else {
        //cerr << "ADD " << a[i] << " -> T" << nl;
        g.add_edge(i, sink);
      }
    }

    return (int)size(a) - g.flow(source, sink);
  };

  int ans = solve(all);
  if(one) {
    ans = max(ans, 1 + solve(other));
  }
  cout << ans << nl;
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
