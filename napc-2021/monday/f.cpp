#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

vector<pt> read_poly() {
  int n;
  cin >> n;
  vector<pt> v;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    v.emplace_back(x, y);
  }
  return v;
}

namespace ubc {
  using pol = vector<pt>;
ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
// dist(const pt& a, const pt& b) ==> abs(a-b)
bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
int sgn(const ld& x) { return abs(x) < EPS ? 0 : x < 0 ? -1 : 1; }
bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS
    ||  (a.real()<=b.real()+EPS && a.imag()<b.imag()-EPS); }
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS
    ||  (a.imag()<=b.imag()+EPS && a.real()<b.real()-EPS); }

// handles ALL cases, uncomment the 3 marked lines to exclude endpoints
bool seg_x_seg(pt a, pt b, pt c, pt d) {
  //if(eq(a, b) || eq(c, d)) return 0; // exclude endpoints
  ld sa=abs(b-a), sc=abs(d-c); sa=sa>EPS?1/sa:0; sc=sc>EPS?1/sc:0;
  int r1 = sgn(cp(b-a, c-a) * sa), r2 = sgn(cp(b-a, d-a) * sa);
  int r3 = sgn(cp(d-c, a-c) * sc), r4 = sgn(cp(d-c, b-c) * sc);
  if(!r1 && !r2 && !r3) { // collinear
    if(cmp_lex(b, a)) swap(a, b);
    if(cmp_lex(d, c)) swap(c, d);
    //return cmp_lex(a, d) && cmp_lex(c, b); // exclude endpoints
    return !cmp_lex(d, a) && !cmp_lex(b, c);
  } return r1*r2 <= 0 && r3*r4 <= 0; }//change to < to exclude endpoints

// Does NOT include points on the ends of the segment.
inline bool on_segment(const pt &a, const pt &b, const pt &p) {
  return abs(cp(b-a, p-a)) / abs(a-b) < EPS &&
    dp(b-a, p-a)>0 && dp(a-b, p-b)>0; }

// Checks if p lies on the boundary of a polygon v.
inline bool on_boundary(const pol &v, const pt &p) {
  bool res = 0; for(int i=v.size()-1, j=0; j<v.size(); i=j++) {
    res |= on_segment(v[i], v[j], p) || abs(p-v[i]) < EPS; }
  return res; }

// orientation does not matter !!!
bool pt_in_polygon(const pt &p, const pol &v, bool strict=false) {
  if (on_boundary(v,p)) return !strict;
  ld res = 0; for(int i = v.size() - 1, j = 0; j < v.size(); i = j++) {
    res += atan2(cp(v[i] - p, v[j] - p), dp(v[i] - p, v[j] - p)); }
  return abs(res) > 1; } // will be either 2*PI or 0
}

struct cmp {
  bool operator () (const ld& a, const ld& b) const {
    return a < b - EPS;
  }
};

struct Item {
  int u;
  ld angle, d;
  Item(int _u, ld _a, ld _d): u(_u), angle(_a), d(_d) {}
  bool operator < (const Item& o) const {
    return d > o.d;
  }
};

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

  vector<pt> inner = read_poly();
  vector<pt> outer = read_poly();
  int n = inner.size();
  int m = outer.size();

  vector<pt> points = inner;
  points.insert(end(points), begin(outer), end(outer));
  vector<vector<int>> adj(points.size());

  pt base = accumulate(begin(inner), end(inner), pt(0));
  base /= n; // centroid

  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      pt mid = (inner[i] + inner[j]) / (ld)2;
      if(ubc::pt_in_polygon(mid, inner, true)) {
        base = mid; // inside polygon is good for reference
        continue;
      }
      bool ok = true;
      for(int ii=n-1, jj=0; jj<n && ok; ii=jj++) {
        if(ii == i || jj == i || ii == j || jj == j) continue;
        ok &= !ubc::seg_x_seg(inner[i], inner[j], inner[ii], inner[jj]);
      }
      for(int ii=m-1, jj=0; jj<m && ok; ii=jj++) {
        ok &= !ubc::seg_x_seg(inner[i], inner[j], outer[ii], outer[jj]);
      }
      if(ok) {
        adj[i].push_back(j);
        adj[j].push_back(i);
      }
    }
  }

  for(int i=0; i<m; i++) {
    for(int j=0; j<i; j++) {
      pt mid = (outer[i] + outer[j]) / (ld)2;
      if(!ubc::pt_in_polygon(mid, outer, false)) continue;
      bool ok = true;
      for(int ii=m-1, jj=0; jj<m && ok; ii=jj++) {
        if(ii == i || jj == i || ii == j || jj == j) continue;
        ok &= !ubc::seg_x_seg(outer[i], outer[j], outer[ii], outer[jj]);
      }
      for(int ii=n-1, jj=0; jj<n && ok; ii=jj++) {
        ok &= !ubc::seg_x_seg(outer[i], outer[j], inner[ii], inner[jj]);
      }
      if(ok) {
        adj[n+i].push_back(n+j);
        adj[n+j].push_back(n+i);
      }
    }
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      pt mid = (inner[i] + outer[j]) / (ld)2;
      if(ubc::pt_in_polygon(mid, inner, false)) continue; // ???
      if(!ubc::pt_in_polygon(mid, outer, true)) continue; // ???
      bool ok = true;
      for(int ii=n-1, jj=0; jj<n && ok; ii=jj++) {
        if(ii == i || jj == i) continue;
        ok &= !ubc::seg_x_seg(inner[i], outer[j], inner[ii], inner[jj]);
      }
      for(int ii=m-1, jj=0; jj<m && ok; ii=jj++) {
        if(ii == j || jj == j) continue;
        ok &= !ubc::seg_x_seg(inner[i], outer[j], outer[ii], outer[jj]);
      }
      if(ok) {
        adj[i].push_back(n+j);
        adj[n+j].push_back(i);
      }
    }
  }

  ld ans = numeric_limits<ld>::infinity();
  for(int s=0; s<n; s++) {
    vector<map<ld, ld, cmp>> dist(n+m);
    priority_queue<Item> dijk;
    dijk.emplace(s, 0, 0);
    while(!dijk.empty()) {
      auto [u, angle, d] = dijk.top();
      dijk.pop();
      if(u == s && abs(angle) > 1) {
        ans = min(ans, d);
        break;
      }
      if(dist[u].count(angle)) continue;
      dist[u][angle] = d;
      for(int v : adj[u]) {
        ld d_dist = abs(points[u] - points[v]);
        ld d_angle = arg((points[v] - base) / (points[u] - base));
        dijk.emplace(v, angle + d_angle, d + d_dist);
      }
    }
  }

  cout << ans << nl;

  return 0;
}
