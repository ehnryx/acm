#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "geometry/lines.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-11L;
random_device _rd; mt19937 rng(_rd());

using pt = point<ld>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<pair<pt, pt>> segs;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    segs.emplace_back(pt{(ld)a, (ld)b}, pt{(ld)x, (ld)y});
  }

  auto [start, vs] = [&]{
    ld a, b, v;
    cin >> a >> b >> v;
    return tuple(pt{a, b}, v);
  }();

  auto [fs, ft, vf] = [&]{
    ld a, b, x, y, v;
    cin >> a >> b >> x >> y >> v;
    return tuple(pt{a, b}, pt{x, y}, v);
  }();

  vector<vector<pair<ld, int>>> lines(n);
  vector<ld> sinks;
  int verts = 0;
  int source = -1;
  for(int i=0; i<n; i++) {
    //cerr << verts << " -> " << segs[i].first << endl;
    lines[i].emplace_back(0, verts++);
    //cerr << verts << " -> " << segs[i].second << endl;
    lines[i].emplace_back(abs(segs[i].first - segs[i].second), verts++);
    for(int j=0; j<i; j++) {
      if(seg_x_seg(EPS, segs[i].first, segs[i].second, segs[j].first, segs[j].second)) {
        auto it = line_inter(segs[i].first, segs[i].second, segs[j].first, segs[j].second);
        lines[i].emplace_back(abs(it - segs[i].first), verts);
        lines[j].emplace_back(abs(it - segs[j].first), verts);
        //cerr << verts << " -> " << it << endl;
        verts++;
      }
    }
    if(seg_x_seg(EPS, start, start, segs[i].first, segs[i].second)) {
      lines[i].emplace_back(abs(start - segs[i].first), verts);
      //cerr << verts << " -> " << start << endl;
      source = verts++;
    }
    if(seg_x_seg(EPS, fs, ft, segs[i].first, segs[i].second)) {
      auto it = line_inter(fs, ft, segs[i].first, segs[i].second);
      //cerr << verts << " -> " << it << endl;
      lines[i].emplace_back(abs(it - segs[i].first), verts++);
      sinks.resize(verts, -2);
      sinks[verts - 1] = abs(it - fs) / vf;
    }
  }
  sinks.resize(verts, -2);
  assert(source != -1);

  vector<vector<pair<int, ld>>> adj(verts);
  for(int i=0; i<n; i++) {
    sort(begin(lines[i]), end(lines[i]));
    for(int j=1; j<size(lines[i]); j++) {
      auto [du, u] = lines[i][j];
      auto [dv, v] = lines[i][j-1];
      adj[u].emplace_back(v, abs(du - dv) / vs);
      adj[v].emplace_back(u, abs(du - dv) / vs);
    }
  }

  vector<ld> dist(verts, -2);
  struct item {
    int u; ld d;
    bool operator<(const item& o) const {
      return d > o.d;
    }
  };
  priority_queue<item> dijk;
  dijk.push(item{source, 0});
  while(not empty(dijk)) {
    auto [u, d] = dijk.top();
    dijk.pop();
    if(dist[u] > -1) continue;
    dist[u] = d;
    for(auto [v, c] : adj[u]) {
      if(dist[v] > -1) continue;
      dijk.push(item{v, d + c});
    }
  }

  ld ans = 2e42;
  for(int i=0; i<verts; i++) {
    if(dist[i] > -1 and dist[i] < sinks[i] + 1e-9) {
      //cerr << "AT " << i << " -> " << dist[i] << " vs " << sinks[i] << endl;
      ans = min(ans, sinks[i]);
    }
  }
  if(ans < 1e42) {
    cout << ans << nl;
  } else {
    cout << "Impossible" << nl;
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
