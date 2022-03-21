#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


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

  struct Item {
    int i, j, d;
    Item(int _i, int _j, int _d): i(_i), j(_j), d(_d) {} // c++17
    bool operator < (const Item& o) const {
      return d > o.d;
    }
  };
  priority_queue<Item> dijk;
  dijk.emplace(start.first, start.second, 0);
  vector dist(n + 2, vector<int>(m + 2, -1));
  while(!empty(dijk)) {
    auto [i, j, d] = dijk.top();
    dijk.pop();
    if(dist[i][j] != -1) continue;
    dist[i][j] = d;
    for(auto [di, dj] : transitions) {
      if(dist[i+di][j+dj] == -1 && g[i+di][j+dj] != '#') {
        dijk.emplace(i+di, j+dj, d + deg[i][j]);
      }
    }
  }

  cout << (ld)dist[end.first][end.second] / total << nl;

  return 0;
}
