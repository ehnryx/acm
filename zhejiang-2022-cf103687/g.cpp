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


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  vector<pair<int, int>> p;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    p.emplace_back(x, y);
  }

  int sx, sy, tx, ty;
  cin >> sx >> sy >> tx >> ty;
  const int source = size(p);
  p.emplace_back(sx, sy);
  const int sink = size(p);
  p.emplace_back(tx, ty);

  int v1, v2;
  cin >> v1 >> v2;

  auto cost = [v1, v2](pair<int, int> s, pair<int, int> t, bool glide) {
    int dx = s.first - t.first;
    int dy = s.second - t.second;
    double dist = sqrt((ll)dx*dx + (ll)dy*dy);
    if(!glide) {
      return dist / v1;
    } else if(dist <= v2 * 3) {
      return dist / v2;
    } else {
      return 3 + (dist - v2 * 3) / v1;
    }
  };

  struct Item {
    int u;
    double d;
    bool operator < (const Item& o) const {
      return d > o.d;
    }
  };

  vector<double> dist(size(p), -1);

  priority_queue<Item> dijk;
  dijk.emplace(source, 0);
  while(!empty(dijk)) {
    auto [u, d] = dijk.top();
    dijk.pop();
    if(dist[u] != -1) continue;
    dist[u] = d;
    for(int v=0; v<size(p); v++) {
      if(dist[v] == -1) {
        dijk.emplace(v, d + cost(p[u], p[v], u < n));
      }
    }
  }

  cout << dist[sink] << nl;

  return 0;
}
