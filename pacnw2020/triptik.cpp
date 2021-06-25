#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

const char nl = '\n';
using ll = long long;
using ld = long double;

struct top_4 {
  int a, b, c, d;
  top_4() = default;
  void add(int v) {
    if (v > a) {
      d = c; c = b; b = a; a = v;
    } else if (v > b) {
      d = c; c = b; b = v;
    } else if (v > c) {
      d = c; c = v;
    } else if (v > d) {
      d = v;
    }
  }
  vector<int> get_vector(int k) const {
    if (k == 1) return { a };
    else if (k == 2) return { a, b };
    else if (k == 3) return { a, b, c };
    else if (k == 4) return { a, b, c, d };
    else assert(false);
  }
  vector<int> get(int k) const {
    vector<int> res = get_vector(k);
    while (!empty(res) && res.back() == 0) {
      res.pop_back();
    }
    return res;
  }
};

struct node {
  top_4 vals;
  node() = default;
  void put(int v) { vals.add(v); }
  top_4 get() const { return vals; }
  static top_4 default_value() { return top_4(); }
  static top_4 merge(top_4 a, const top_4& b) {
    for (int v : b.get(4)) {
      a.add(v);
    }
    return a;
  }
};

const int L = 30;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  cin >> n >> k;

  vector<int> pos(n + 1);
  map<int, int> remap;
  for (int i = 1; i <= n; i++) {
    cin >> pos[i];
    pos[i] *= 2; // window bounds are always half-integer points
    remap[pos[i]];
  }
  remap[0]; // remap center as well

  int rid = 0;
  for (auto& it : remap) {
    it.second = rid++;
  }

  segment_tree<node, top_4, false> st(rid);
  for (int i = 1; i <= n; i++) {
    st.update_up(remap[pos[i]], i);
  }

  function<top_4(int, int)> query = [&](int x, int r) {
    int left = x - r;
    int right = x + r;
    left = remap.lower_bound(left)->second;
    right = prev(remap.upper_bound(right))->second;
    return st.query_range(left, right);
  };

  vector dist(rid, vector<int>(L, -1));
  queue<pair<int, int>> bfs;
  bfs.emplace(0, 1);
  dist[remap[0]][1] = 0;
  while (!empty(bfs)) {
    auto [x, zoom] = bfs.front();
    bfs.pop();
    int u = remap[x];
    if (zoom > 0 && dist[u][zoom - 1] == -1) {
      bfs.emplace(x, zoom - 1);
      dist[u][zoom - 1] = dist[u][zoom] + 1;
    }
    if (zoom + 1 < L && dist[u][zoom + 1] == -1) {
      bfs.emplace(x, zoom + 1);
      dist[u][zoom + 1] = dist[u][zoom] + 1;
    }
    for (int i : query(x, 1 << zoom).get(k)) {
      int to = pos[i];
      int v = remap[to];
      if (dist[v][zoom] == -1) {
        bfs.emplace(to, zoom);
        dist[v][zoom] = dist[u][zoom] + 1;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    int ans = numeric_limits<int>::max();
    for (int j = 0; j < L; j++) {
      vector<int> visible = query(pos[i], 1 << j).get(k);
      if (find(begin(visible), end(visible), i) != end(visible)) {
        ans = min(ans, dist[remap[pos[i]]][j]);
      }
    }
    cout << ans << nl;
  }

  return 0;
}
