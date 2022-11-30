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

  vector<vector<int>> ans(n);
  for(int i=0; i<n; i++) {
    ans[i].push_back(i + 1);
  }

  queue<int> bfs;
  vector<int> done(n);
  vector<int> total(n);
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      total[i] += g[j][i];
    }
    if(total[i] == done[i]) {
      bfs.push(i);
    }
  }
  while(not empty(bfs)) {
    int u = bfs.front();
    bfs.pop();
    for(int i=0; i<n; i++) {
      if(not g[u][i]) continue;
      vector<int> out;
      set_union(begin(ans[i]), end(ans[i]), begin(ans[u]), end(ans[u]), back_inserter(out));
      ans[i] = out;
      if(++done[i] == total[i]) {
        bfs.push(i);
      }
    }
  }

  for(int i=0; i<n; i++) {
    cout << size(ans[i]);
    for(int v : ans[i]) {
      cout << " " << v;
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
