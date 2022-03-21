#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/math/matrix.h"
#include "../../../lca/number/float_with_eps.h"

using ll = long long;
//using ld = long double;
//using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
//constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

// this doesn't work on kattis because c++17
// fails with eps = 0 as expected
using ld = float_with_eps<long double, 1e-11L>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  string line;
  getline(cin, line);

  vector g(n + 2, vector<char>(m + 2, '#'));
  pair<int, int> start, end;
  for(int i=1; i<=n; i++) {
    getline(cin, line);
    for(int j=1; j<=m; j++) {
      g[i][j] = line[j-1];
      if(g[i][j] == 'E') {
        start = pair(i, j);
      } else if(g[i][j] == 'D') {
        end = pair(i, j);
      }
    }
  }

  //static constexpr array transitions = {
  static constexpr auto transitions = { // c++17
    pair(1, 0),
    pair(-1, 0),
    pair(0, 1),
    pair(0, -1),
  };

  int total = 0;
  vector deg(n + 2, vector<int>(m + 2));
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(g[i][j] != ' ') continue;
      for(auto [di, dj] : transitions) {
        if(g[i+di][j+dj] == ' ') {
          deg[i][j]++;
          total++;
        }
      }
    }
  }

  auto get = [&](int i, int j) {
    return (i-1) * m + (j-1);
  };

  vector<vector<ld>> eqs;
  vector<ld> sum(n*m + 1);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(g[i][j] != ' ') continue;
      sum[get(i, j)] = 1;
      vector<ld> row(n*m + 1); // +1 for rhs
      row[get(i, j)] = -1;
      for(auto [di, dj] : transitions) {
        if(g[i+di][j+dj] == ' ') {
          row[get(i+di, j+dj)] = (ld)1 / deg[i+di][j+dj];
        }
      }
      eqs.push_back(move(row));
    }
  }
  sum.back() = 1;
  eqs.push_back(move(sum)); // probabilities sum to 1

  matrix mat(move(eqs));
  //cerr << "MATRIX: " << mat << nl;
  mat.solve();
  //cerr << "RREF: " << mat << nl;
  const auto& pbs = mat.ans;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      //cerr << i << " " << j << " -> " << pbs[get(i, j)] << " free? " << mat.is_free[get(i, j)] << nl;
    }
  }

  struct Item {
    int i, j;
    ld d;
    Item(int _i, int _j, ld _d): i(_i), j(_j), d(_d) {} // c++17
    bool operator < (const Item& o) const {
      return d > o.d;
    }
  };
  priority_queue<Item> dijk;
  dijk.emplace(start.first, start.second, 0);
  vector dist(n + 2, vector<ld>(m + 2, -1));
  while(!empty(dijk)) {
    auto [i, j, d] = dijk.top();
    dijk.pop();
    if(dist[i][j] != -1) continue;
    dist[i][j] = d;
    for(auto [di, dj] : transitions) {
      if(dist[i+di][j+dj] == -1 && g[i+di][j+dj] != '#') {
        dijk.emplace(i+di, j+dj, d + pbs[get(i, j)]);
      }
    }
  }

  cout << dist[end.first][end.second] << nl;

  return 0;
}
