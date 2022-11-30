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
  string s;
  cin >> s;
  vector<int> a;
  transform(begin(s), end(s), back_inserter(a),
      [](char c) {
        switch(c) {
        case 'c': return 0;
        case 'd': return 1;
        case 'h': return 2;
        case 's': return 3;
        default: assert(false);
        }
      });
  int n = size(a);

  int ans = n;

  vector<int> suits(4);
  iota(begin(suits), end(suits), 0);
  do {
    vector<int> before(4, -1);
    for(int i=1; i<4; i++) {
      before[suits[i]] = suits[i-1];
    }
    vector<vector<int>> adj(n);
    vector<int> indeg(n);
    vector<int> last(4, -1);
    for(int i=0; i<n; i++) {
      if(last[a[i]] != -1) {
        adj[last[a[i]]].push_back(i);
        indeg[i]++;
      }
      if(before[a[i]] != -1 and last[before[a[i]]] != -1) {
        adj[last[before[a[i]]]].push_back(i);
        indeg[i]++;
      }
      last[a[i]] = i;
    }

    queue<int> bfs;
    vector<int> dist(n);
    for(int i=0; i<n; i++) {
      if(indeg[i] == 0) {
        bfs.push(i);
      }
    }
    while(not empty(bfs)) {
      int u = bfs.front();
      bfs.pop();
      for(int v : adj[u]) {
        dist[v] = max(dist[v], dist[u] + 1);
        if(--indeg[v] == 0) {
          bfs.push(v);
        }
      }
    }
    int path = *max_element(begin(dist), end(dist)) + 1;
    ans = min(ans, n - path);
  } while(next_permutation(begin(suits), end(suits)));

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
