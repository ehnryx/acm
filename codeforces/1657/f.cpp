#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "tree/rooted_tree.h"
%:include "graph/two_sat.h"

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
  vector<vector<int>> adj(n+1);
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  rooted_tree g(move(adj), 1);

  vector<pair<char, char>> options(g.size());
  two_sat sat(g.size() + m);
  auto word = [n=g.size()](int i) -> int {
    return n + i;
  };

  for(int i=0; i<m; i++) {
    int a, b; string s;
    cin >> a >> b >> s;

    vector<int> path(size(s));
    int front = 0;
    int back = size(s);
    if(g.depth[a] < g.depth[b]) swap(a, b);
    while(g.depth[a] > g.depth[b]) {
      path[front++] = a;
      a = g.parent[a];
    }
    while(a != b) {
      path[front++] = a;
      path[--back] = b;
      a = g.parent[a];
      b = g.parent[b];
    }
    path[front++] = a;
    assert(front == back);

    for(int j=0; j<size(s); j++) {
      if(!options[path[j]].first) {
        options[path[j]] = pair(s[j], s[size(s)-1 - j]);
      }
      auto [x, y] = options[path[j]];
      if(s[j] != x) {
        sat.implies(path[j], true, word(i), false);
      }
      if(s[j] != y) {
        sat.implies(path[j], false, word(i), false);
      }
      if(s[size(s)-1 - j] != x) {
        sat.implies(path[j], true, word(i), true);
      }
      if(s[size(s)-1 - j] != y) {
        sat.implies(path[j], false, word(i), true);
      }
    }
  }

  if (!sat.solve()) {
    cout << "NO" << nl;
  } else {
    cout << "YES" << nl;
    for(int i=1; i<=n; i++) {
      char ans = (sat[i] ? options[i].first : options[i].second);
      cout << (ans ? ans : 'a');
    }
    cout << nl;
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
