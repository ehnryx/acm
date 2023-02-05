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
  string line;
  getline(cin, line);

  vector g(n + 2, vector<char>(m + 2, 'X'));
  vector<pair<int, int>> sources;
  int totaal = 0;
  for(int i=1; i<=n; i++) {
    getline(cin, line);
    for(int j=1; j<=m; j++) {
      g[i][j] = line[j-1];
      totaal += (g[i][j] == '.');
      if(isalpha(g[i][j]) and g[i][j] != 'X') {
        sources.emplace_back(i, j);
      }
    }
  }

  int goed = 0;
  int aantal = 0;
  for(auto [si, sj] : sources) {
    if(g[si][sj] == 'X') continue;
    queue<pair<int, int>> bfs;
    bfs.emplace(si, sj);
    g[si][sj] = 'X';
    int cur = 0;
    while(not empty(bfs)) {
      auto [i, j] = bfs.front();
      bfs.pop();
      for(auto [di, dj] : {
          pair(0, 1), pair(1, 0), pair(-1, 0), pair(0, -1) }) {
        int ni = i + di;
        int nj = j + dj;
        if(not isalpha(g[ni][nj])) {
          cur += (g[ni][nj] == '.');
          g[ni][nj] = 'X';
          bfs.emplace(ni, nj);
        }
      }
    }
    goed += cur;
    aantal += !!cur;
  }

  cout << aantal << " " << totaal - goed << nl;
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
