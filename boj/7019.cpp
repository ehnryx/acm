#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/nd_array.h"
//%:include "utility/output.h"

%:include "geometry/circle.h"
%:include "graph/dijkstra.h"

using ll = long long;
using ld = double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Point = point<int>;
using Circle = circle<int>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  for(int n; cin >> n and n; ) {
    vector<Circle> circles;
    for(int i=0; i<n; i++) {
      int x, y, r;
      cin >> x >> y >> r;
      circles.emplace_back(Point(x, y), r);
    }
    vector<decltype(declval<Circle>().intersect(declval<Circle>()).get_one())> p;
    p.emplace_back(circles.front().center);
    p.emplace_back(circles.back().center);
    for(int i=0; i<n; i++) {
      for(int j=0; j<i; j++) {
        auto it = circles[i].intersect(circles[j]);
        auto jt = circles[j].intersect(circles[i]);
        assert(it.count() == 0 or it.count() == 2);
        assert((abs(i - j) == 1) == (it.count() == 2));
        if(it.count() != 2) continue;
        auto [u, v] = it.get_two();
        auto [jv, ju] = jt.get_two();
        assert(abs(u - ju) < EPS and abs(v - jv) < EPS);
        p.push_back(u);
        p.push_back(v);
      }
    }

    graph_t<ld> g(size(p));

    for(int i=0; i<size(p); i++) {
      for(int j=0; j<i; j++) {
        //cerr << "CHECK " << i << " " << j << " : " << p[i] << " -- " << p[j] << endl;
        auto d2 = norm(p[j] - p[i]);
        vector<pair<ld, int>> ev;
        for (const auto& c : circles) {
          auto it = c.intersect(p[i], p[j]);
          if(it.count() != 2) continue;
          auto [u, v] = it.get_two();
          using I = decay_t<decltype(u)>;
          auto s = dot(u - I(p[i]), I(p[j] - p[i])) / d2 - EPS;
          auto t = dot(v - I(p[i]), I(p[j] - p[i])) / d2 + EPS;
          //cerr << "GET intersections " << u << " " << v << " -> " << s << " .. " << t << endl;
          ev.emplace_back(s, 1);
          ev.emplace_back(t, -1);
        }
        ev.emplace_back(0, 0);
        ev.emplace_back(1, 0);
        sort(begin(ev), end(ev));
        bool ok = true;
        int depth = 0;
        for(auto [d, s] : ev) {
          depth += s;
          if(depth == 0 and 0 <= d and d <= 1) {
            ok = false;
            break;
          }
        }
        if(ok) {
          //cerr << "ADD EDGE " << i << " " << j << " : " << p[i] << " -- " << p[j] << " : " << abs(p[i] - p[j]) << endl;
          g.add_edge(i, j, abs(p[i] - p[j]));
        }
      }
    }

    cout << dijkstra(g, typename decltype(g)::weight_t(-1)).run(0).dist[1] << nl;
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
