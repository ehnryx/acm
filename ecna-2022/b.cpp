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

constexpr array dirs = {
  pair(-1,  1), pair(0,  1), pair(1,  1),
  pair(-1,  0),              pair(1,  0),
  pair(-1, -1), pair(0, -1), pair(1, -1),
};
static_assert(size(dirs) == 8);

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector g(n, vector<char>(m));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
    }
  }

  int ks;
  cin >> ks;
  string pat;
  cin >> pat;

  struct state {
    int x, i, j, k, d; // index x, (i, j) with k kinks so far, from direction d
    bool operator<(const state& o) const {
      return tie(x, i, j, k, d) < tie(o.x, o.i, o.j, o.k, o.d);
    }
  };

  bool vis[100][10][10][100][9];
  memset(vis, 0, sizeof vis);
  //set<state> vis;
  auto solve = [&](auto&& self, state at) -> bool {
    if(pat[at.x] != g[at.i][at.j]) return false;
    if(at.x + 1 == size(pat)) return at.k == ks;
    //if(vis.count(at)) return false;
    if(vis[at.x][at.i][at.j][at.k][at.d]) return false;
    for(int d=0; d<size(dirs); d++) {
      auto [di, dj] = dirs[d];
      int i = at.i + di;
      int j = at.j + dj;
      if(0 <= i and i < n and 0 <= j and j < m) {
        if(self(self, state{ at.x + 1, i, j, at.k + (at.d != d and at.d != 8), d })) {
          return true;
        }
      }
    }
    //vis.insert(at);
    vis[at.x][at.i][at.j][at.k][at.d] = true;
    return false;
  };

  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      if(solve(solve, state{ 0, i, j, 0, 8 })) {
        return void(cout << "Yes" << nl);
      }
    }
  }

  cout << "No" << nl;
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
