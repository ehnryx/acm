#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/push_relabel.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m, t;
  cin >> n >> m >> t;
  enum { IN, OUT };
  auto get = [n,m,t](int i, int j, int k, int dir) {
    return 2 * (k*n*m + i*m + j) + dir;
  };

  vector g(n, vector<char>(m));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
    }
  }

  push_relabel<int> graph(n*m*(t+1) * 2 + 2);
  const int source = n*m*(t+1) * 2;
  const int sink = source + 1;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      for(auto [di, dj] : {
          pair(0, 1), pair(1, 0), pair(-1, 0), pair(0, -1), pair(0, 0) }) {
        int ni = i + di;
        int nj = j + dj;
        if(ni < 0 or n <= ni or nj < 0 or m <= nj) continue;
        for(int k=0; k<t; k++) {
          graph.add_edge(get(i, j, k, OUT), get(ni, nj, k+1, IN), 1);
        }
      }
      if(g[i][j] == 'P') {
        graph.add_edge(source, get(i, j, 0, IN), 1);
      } else if(g[i][j] == 'E') {
        for(int k=0; k<=t; k++) {
          graph.add_edge(get(i, j, k, OUT), sink, 1);
        }
      }
      if(g[i][j] != '#') {
        for(int k=0; k<=t; k++) {
          graph.add_edge(get(i, j, k, IN), get(i, j, k, OUT), 1);
        }
      }
    }
  }

  cout << graph.flow(source, sink) << nl;
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
