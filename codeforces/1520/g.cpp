#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/graph/dijkstra.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const vector<pair<int,int>> dxy = {
  {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

struct graph {
  int n, m, w;
  vector<vector<int>> grid;
  graph(int _n, int _m, int _w): n(_n), m(_m), w(_w), grid(n, vector<int>(m)) {}
  int size() const { return n*m + 1; }
  int& at(int i, int j) { return grid[i][j]; }
  vector<pair<int,int>> operator [] (int x) const {
    if(x == n*m) {
      vector<pair<int,int>> portals;
      for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
          if(grid[i][j] > 0) {
            portals.emplace_back(i*m + j, grid[i][j]);
          }
        }
      }
      return portals;
    } else {
      int i = x / m, j = x % m;
      vector<pair<int,int>> nbs;
      for(auto [di, dj] : dxy) {
        if(i+di < 0 || n <= i+di || j+dj < 0 || m <= j+dj) continue;
        if(grid[i+di][j+dj] < 0) continue;
        nbs.emplace_back((i+di)*m + (j+dj), w);
      }
      if(grid[i][j] > 0) nbs.emplace_back(n*m, grid[i][j]);
      return nbs;
    }
  }
};

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m, w;
  cin >> n >> m >> w;
  graph g(n, m, w);
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g.at(i, j);
    }
  }
  auto dists = dijkstra<ll>(g, 0);
  cout << dists[n*m - 1] << nl;

  return 0;
}
