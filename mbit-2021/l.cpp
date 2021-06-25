#pragma GCC optimize("O3")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse4,avx2")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../lca/geometry2d/point.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef /*long*/ double ld;
//typedef complex<ld> pt;
using pt = point<ld>;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

#ifdef M_PIl
const ld PI = M_PIl;
#else
const ld PI = acos((ld)-1);
#endif

ld lp_dist(const pt &a, const pt &b, const pt &p) {
  return cross(b - a, p - a) / abs(b - a); }
// k=0 top-top, k=1 bot-bot, k=2 top-bot, k=3 bot-top
pair<pt, pt> circle_tangent(ld r1, ld r2, ld d, int k) { // use below fn
  ld dr = (k & 2) ? (-r1-r2) : (r2-r1); ld t = asin(dr / d);
  pt p1=polar(r1, PI/2+t), p2=polar(r2, PI/2+t); if(k&2) p2*=-1;
  p2+=pt(d,0);
  if(k&1){ p1=pt(p1.real(),-p1.imag()); p2=pt(p2.real(),-p2.imag()); }
  return make_pair(p1, p2); }
pair<pt, pt> circle_tangent(pt p1, ld r1, pt p2, ld r2, int k) {
  // translate/rotate so c1 at (0,0), c2 at x-axis
  pt d = p2-p1; auto p = circle_tangent(r1,r2,abs(d),k); d /= abs(d);
  p.first *= d; p.second *= d; p.first += p1; p.second += p1; return p;
}

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

  int n;
  cin >> n;
  vector<pt> c(n+2);
  vector<int> r(n+2), d(n+2);

  int x, y;
  cin >> x >> y;
  c[n] = pt(x, y);
  cin >> x >> y;
  c[n+1] = pt(x, y);
  for(int i=0; i<n; i++) {
    cin >> x >> y >> r[i] >> d[i];
    c[i] = pt(x, y);
  }

  vector<vector<pair<ld,int>>> circle(n+2); // angle, id
  vector<vector<pair<int,ld>>> adj(2 * (n*n*2 + 2*n + 7));
  int pid = 2;
  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      for(int t=0; t<4; t++) {
        auto [ti, tj] = circle_tangent(c[i], r[i], c[j], r[j], t);
        int a, b;
        circle[i].emplace_back(arg(ti - c[i]), a = pid++);
        circle[j].emplace_back(arg(tj - c[j]), b = pid++);
        ld dist = abs(ti - tj);
        for(int k=0; k<n; k++) {
          if(k == i || k == j) continue;
          if(abs(lp_dist(ti, tj, c[k])) < r[k] // - EPS
              && dot(c[k] - ti, tj - ti) > 0 && dot(c[k] - tj, ti - tj) > 0) {
            dist += d[k];
          }
        }
        adj[a].emplace_back(b, dist);
        adj[b].emplace_back(a, dist);
      }
    }
  }

  for(int i=n; i<n+2; i++) {
    for(int j=0; j<n; j++) {
      for(int t : {0, 2}) {
        auto [ti, tj] = circle_tangent(c[i], r[i], c[j], r[j], t);
        int a = i-n, b = pid++;
        circle[j].emplace_back(arg(tj - c[j]), b);
        ld dist = abs(ti - tj);
        for(int k=0; k<n; k++) {
          if(k == j) continue;
          if(abs(lp_dist(ti, tj, c[k])) < r[k] // - EPS
              && dot(c[k] - ti, tj - ti) > 0 && dot(c[k] - tj, ti - tj) > 0) {
            dist += d[k];
          }
        }
        adj[a].emplace_back(b, dist);
        adj[b].emplace_back(a, dist);
      }
    }
  }

  {
    ld dist = abs(c[n] - c[n+1]);
    pt ti = c[n], tj = c[n+1];
    for(int k=0; k<n; k++) {
      if(abs(lp_dist(ti, tj, c[k])) < r[k] // - EPS
          && dot(c[k] - ti, tj - ti) > 0 && dot(c[k] - tj, ti - tj) > 0) {
        dist += d[k];
      }
    }
    adj[0].emplace_back(1, dist);
    adj[1].emplace_back(0, dist);
  }

  for(int i=0; i<n; i++) {
    sort(begin(circle[i]), end(circle[i]));
    int m = circle[i].size();
    for(int j=m-1, k=0; k<m; j=k++) {
      ld diff = circle[i][k].first - circle[i][j].first;
      assert(diff == diff);
      while(diff < 0) diff += PI;
      diff *= r[i];
      int a = circle[i][k].second;
      int b = circle[i][j].second;
      adj[a].emplace_back(b, diff);
      adj[b].emplace_back(a, diff);
    }
  }

  vector<bool> vis(pid);
  vector<ld> dist(pid, -1);
  priority_queue<pair<ld,int>, vector<pair<ld,int>>, greater<>> dijk;
  dist[0] = 0;
  dijk.push({0, 0});
  while(!empty(dijk)) {
    auto [ds, u] = dijk.top();
    dijk.pop();
    if(u == 1) {
      cout << ds << nl;
      return 0;
    }
    if(vis[u]) continue;
    vis[u] = true;
    for(auto [v, e] : adj[u]) {
      if(dist[v] == -1 || ds + e < dist[v]) {
        dist[v] = ds + e;
        dijk.push({dist[v], v});
      }
    }
  }

  assert(false);

  return 0;
}
