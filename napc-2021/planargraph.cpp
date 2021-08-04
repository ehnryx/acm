#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

using ld = double;
using pt = complex<ld>;

constexpr char nl = '\n';
random_device _rd; mt19937 rng(_rd());



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

  int n, m;
  cin >> n >> m;

  static vector<pt> orig(n);
  vector<tuple<pt, int, bool>> points;  // (x,y), id, is_query?
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    points.emplace_back(orig[i] = pt(x, y), i, false);
  }

  vector<vector<pair<int, int>>> edges(n);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    edges[a-1].emplace_back(b-1, c);
    edges[b-1].emplace_back(a-1, c);
  }

  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    ld a, b, x, y;
    cin >> a >> b >> x >> y;
    points.emplace_back(pt(a, b), i, true);
    points.emplace_back(pt(x, y), i, true);
  }

  static const pt rotation = polar((ld)1, (ld)1.789);  // VIVE LA REVOLUTION
  for (auto& v : orig) {
    v *= rotation;
  }
  for (auto& [v, _, __] : points) {
    v *= rotation;
  }
  sort(begin(points), end(points), [](const auto& a, const auto& b) {
      return get<0>(a).real() < get<0>(b).real(); });

  struct Edge {
    int a, b;
    unsigned int c;
    Edge(int _a, int _b, int _c): a(_a), b(_b), c(_c) {}
    bool operator < (const Edge& o) const {
      return c < o.c;
    }
  };

  // dual graph stuff
  int face_id = 1;
  vector<Edge> adj;
  vector<vector<int>> endpoints(1);
  vector<int> dsu(1, -1);
  function<int(int)> find = [&](int i) {
    if(dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  };
  function<void(int, int)> link = [&](int i, int j) {
    i = find(i);
    j = find(j);
    if (i != j) {
      dsu[i] = j;
    }
  };

  adj.reserve(2 * n);
  endpoints.reserve(2 * n);
  dsu.reserve(2 * n);

  function<int(void)> new_face = [&]() {
    endpoints.emplace_back();
    dsu.emplace_back(-1);
    return face_id++;
  };

  // segments

  static ld base_x = -1e9;
  struct Segment {
    int l, r;  // orig[l] --> orig[r]
    ld slope;
    Segment(int _l, int _r): l(_l), r(_r) {
      slope = (orig[l].imag() - orig[r].imag()) / (orig[l].real() - orig[r].real());
    }
    bool operator < (const Segment& o) const {
      ld y = get_y(base_x);
      ld oy = o.get_y(base_x);
      if (y != oy) return y < oy;
      if (l == o.l) return slope < o.slope;
      return slope > o.slope;
    }
    bool operator < (const ld& y) const {
      return get_y(base_x) < y;
    }
    ld get_y(const ld& x) const {
      if (x == orig[l].real()) return orig[l].imag();
      if (x == orig[r].real()) return orig[r].imag();
      ld ratio = (x - orig[l].real()) / (orig[r].real() - orig[l].real());
      return ratio * (orig[r].imag() - orig[l].imag()) + orig[l].imag();
    }
  };

  // sweep

  map<Segment, int, less<>> segs;
  for (const auto& [v, id, is_query] : points) {
    ld x = v.real();
    ld y = v.imag();

    if (is_query) {
      base_x = x;
      auto it = segs.lower_bound(y);
      int face = (it == segs.begin() ? 0 : prev(it)->second);
      endpoints[face].push_back(id);
    }

    else {
      base_x = x;

      int rem = 0;
      vector<pair<Segment, int>> add;
      for (auto [nb, weight] : edges[id]) {
        if (real(orig[nb]) < x) { // merge
          rem += 1;
        } else { // add outgoing edges
          add.emplace_back(Segment(id, nb), weight);
          //cerr << "primal edge " << id << " " << nb << nl;
        }
      }

      int top, bot;
      auto it = segs.lower_bound(y);
      if (!rem) {
        if (it == segs.begin()) {
          top = bot = 0;
        } else {
          top = bot = prev(it)->second;
        }
      } else {
        while (rem--) {
          top = it->second;
          it = segs.erase(it);
        }
        bot = (it == segs.begin() ? 0 : prev(it)->second);
      }

      if (empty(add)) {
        link(top, bot);
      } else {
        sort(begin(add), end(add), greater<>());
        segs[add[0].first] = top;
        int last = top;
        int weight = add[0].second;
        for (int i = 1; i < add.size(); i++) {
          int cur = new_face();
          segs[add[i].first] = cur;
          adj.emplace_back(last, cur, weight);  // why is this adj instead of edge :facepalm:
          last = cur;
          weight = add[i].second;
        }
        adj.emplace_back(last, bot, weight);
      }
    }
  }

  vector<int> ans(q);

  vector<set<int>> have(face_id);
  function<void(int, int, int)> link_dual = [&](int i, int j, int c) {
    i = find(i);
    j = find(j);
    if (i == j) return;
    if (have[i].size() > have[j].size()) swap(i, j);
    dsu[i] = j;
    for (int v : have[i]) {
      if (have[j].count(v)) {
        ans[v] = c;
        have[j].erase(v);
      } else {
        have[j].insert(v);
      }
    }
  };

  for (int i = 0; i < face_id; i++) {
    int to = find(i);
    for (int v : endpoints[i]) {
      if (have[to].insert(v).second) {
        // nothing to do here
      } else {
        have[to].erase(v);
        if (to == find(0)) {
          ans[v] = -1;  // sad
        }
      }
    }
  }

  for (auto& [a, b, c] : adj) {
    if(find(a) == find(0) || find(b) == find(0)) {
      c = -1;
    }
  }
  sort(begin(adj), end(adj));
  for (const auto& [a, b, c] : adj) {
    link_dual(a, b, c);
  }

  for (int i = 0; i < q; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
