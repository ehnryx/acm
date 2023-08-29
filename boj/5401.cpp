#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/nd_array.h"
//%:include "utility/output.h"

%:include "geometry/delaunay.h"
%:include "geometry/polygon.h"
%:include "ds/union_find.h"

using ll = long long;
using ld = double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using pt = point<ld>;

struct Edge {
  int u, v;
  ld d;
  bool operator<(const Edge& o) const {
    return d > o.d;
  }
};

#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  ld ans = 1e18;
  vector<pt> p;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    p.emplace_back(a, b);
    ans = min(ans, abs(p.back()) - 2);
  }
  auto triangles = delaunay(p, EPS, (ld)1.618);

  map<pair<int, int>, int> faces;
  vector<Edge> edges;
  int start = -1;
  for(int i=0; i<size(triangles); i++) {
    auto [a, b, c] = triangles[i];
    {
      auto key = pair(min(a, b), max(a, b));
      if(auto it = faces.find(key); it != end(faces)) {
        edges.emplace_back(i, it->second, abs(p[a] - p[b]));
        faces.erase(key);
      } else {
        faces[key] = i;
      }
    }
    {
      auto key = pair(min(b, c), max(b, c));
      if(auto it = faces.find(key); it != end(faces)) {
        edges.emplace_back(i, it->second, abs(p[b] - p[c]));
        faces.erase(key);
      } else {
        faces[key] = i;
      }
    }
    {
      auto key = pair(min(c, a), max(c, a));
      if(auto it = faces.find(key); it != end(faces)) {
        edges.emplace_back(i, it->second, abs(p[c] - p[a]));
        faces.erase(key);
      } else {
        faces[key] = i;
      }
    }
    if(in_polygon(EPS, vector{p[a], p[b], p[c]}, pt(0, 0))) {
      start = i;
    }
  }

  if(start != -1) {
    for(const auto& [key, i] : faces) {
      const auto& [a, b] = key;
      edges.emplace_back(i, size(triangles), abs(p[a] - p[b]));
    }

    sort(begin(edges), end(edges));

    union_find dsu(size(triangles) + 1);
    for(auto [a, b, c] : edges) {
      dsu.link(a, b);
      if(dsu[start] == dsu[size(triangles)]) {
        ans = min(ans, c/2 - 2);
        break;
      }
    }
  }

  cout << (ll)(ans * ans * numbers::pi + EPS) << nl;
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
