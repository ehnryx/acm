#pragma GCC optimize("O3,fast-math")
#pragma GCC target("sse4,avx2")

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/geometry2d/point.h"
#include "../../lca/geometry2d/general.h"

constexpr char nl = '\n';
using ld = double;
using pt = point<ld>;

constexpr ld eps = 1e-13;

pt read() {
  string x, y;
  cin >> x >> y;
  y.pop_back();
  return pt(stoi(x.substr(1)), stoi(y));
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;
  while (T--) {
    int n, mdst;
    cin >> n >> mdst;
    pt source = read();
    pt sink = read();
    vector<ld> surface(n);
    vector<vector<pt>> floes(n);
    for (int i = 0; i < n; i++) {
      int m;
      cin >> m;
      vector<pt> v(m);
      for (int j = 0; j < m; j++) {
        v[j] = read();
      }
      surface[i] = signed_area(v);
      if (surface[i] < 0) {
        reverse(begin(v), end(v));
        surface[i] = -surface[i];
      }
      floes[i] = move(v);
    }

    int s = -1, t = -1;
    vector dist(n, vector<ld>(n, -1));
    for (int i = 0; i < n; i++) {
      if (in_polygon(floes[i], source)) s = i;
      if (in_polygon(floes[i], sink)) t = i;
      for (int j = 0; j < i; j++) {
        ld sep = numeric_limits<ld>::infinity();
        for (size_t ii = 0; ii < floes[i].size(); ii++) {
          size_t ni = ii + 1 == floes[i].size() ? 0 : ii + 1;
          for (size_t jj = 0; jj < floes[j].size(); jj++) {
            size_t nj = jj + 1 == floes[j].size() ? 0 : jj + 1;
            sep = min(sep, segment_point_dist(floes[i][ii], floes[i][ni], floes[j][jj]));
            sep = min(sep, segment_point_dist(floes[j][jj], floes[j][nj], floes[i][ii]));
          }
        }
        if (sep <= mdst + eps) {
          dist[i][j] = dist[j][i] = min(surface[i], surface[j]);
        }
      }
      dist[i][i] = surface[i];
    }

    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          dist[i][j] = max(dist[i][j], min(dist[i][k], dist[k][j]));
        }
      }
    }

    if (dist[s][t] < 0) {
      cout << "Scientists cannot meet" << nl;
    } else {
      cout << fixed << setprecision(9);
      cout << dist[s][t] << nl;
    }
  }

  return 0;
}