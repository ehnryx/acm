#pragma GCC optimize("O3,fast-math")
#pragma GCC target("sse4,avx2")
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
using ld = double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-11L;
random_device _rd; mt19937 rng(_rd());

constexpr ld PI = acos((ld)-1);

const int N = 3000;
//pair<ld, int> ev[N*8];
pair<ld, int> ev[N*4];

struct point {
  int x, y;
} v[N];

//inline ld arg(point A, point B) { return atan2(A.y - B.y, A.x - B.x); }
//inline ld abs(point A, point B) { return sqrt((ll)(A.x - B.x) * (A.x - B.x) + (ll)(A.y - B.y) * (A.y - B.y)); }
#define arg(A, B) atan2(A.y - B.y, A.x - B.x)
#define abs(A, B) sqrt((ll)(A.x - B.x) * (A.x - B.x) + (ll)(A.y - B.y) * (A.y - B.y))

/*
int solve(int n, const vector<pt>& v, int s, int d) {
  //vector<pair<ld, int>> ev;
  int eid = 0;
  for(int i=0; i<n; i++) {
    if(i == s) continue;
    ld angle = arg(v[i] - v[s]);
    ld dist = abs(v[i] - v[s]);
    ld in = angle;
    ld out = angle + PI;
    //ev.emplace_back(in - EPS, 1);
    //ev.emplace_back(out + EPS, -1);
    //ev.emplace_back(in - EPS + 2*PI, 1);
    //ev.emplace_back(out + EPS + 2*PI, -1);
    ev[eid++] = pair(in - EPS, 1);
    ev[eid++] = pair(out + EPS, -1);
    //ev[eid++] = pair(in - EPS + 2*PI, 1);
    //ev[eid++] = pair(out + EPS + 2*PI, -1);
    if (dist > d + EPS) {
      ld diff = asin(d / dist);
      out = angle + diff;
      in = angle + PI - diff;
      //ev.emplace_back(in - EPS, 1);
      //ev.emplace_back(out + EPS, -1);
      //ev.emplace_back(in - EPS + 2*PI, 1);
      //ev.emplace_back(out + EPS + 2*PI, -1);
      ev[eid++] = pair(in - EPS, 1);
      ev[eid++] = pair(out + EPS, -1);
      //ev[eid++] = pair(in - EPS + 2*PI, 1);
      //ev[eid++] = pair(out + EPS + 2*PI, -1);
    }
  }
  //sort(begin(ev), end(ev));
  sort(ev, ev + eid);

  int res = 0;
  int cur = 0;
  //for(auto [_, t] : ev) {
  for(int i=0; i<eid; i++) {
    //cur += t;
    cur += ev[i].second;
    res = max(res, cur);
  }
  return res + 1;
}
*/

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

  int n, d;
  cin >> n >> d;
  //vector<pt> v;
  for(int i=0; i<n; i++) {
    //int a, b;
    //cin >> a >> b;
    //v.emplace_back(a, b);
    cin >> v[i].x >> v[i].y;
  }

  int ans = 0;
  for(int s=0; s<n; s++) {
    //ans = max(ans, solve(n, v, i, d));
    int eid = 0;
    for(int i=0; i<n; i++) {
      if(i == s) continue;
      ld angle = arg(v[i], v[s]);
      ld dist = abs(v[i], v[s]);
      ld in = angle;
      ld out = angle + PI;
      //ev.emplace_back(in - EPS, 1);
      //ev.emplace_back(out + EPS, -1);
      //ev.emplace_back(in - EPS + 2*PI, 1);
      //ev.emplace_back(out + EPS + 2*PI, -1);
      ev[eid++] = pair(in - EPS, 1);
      ev[eid++] = pair(out + EPS, -1);
      //ev[eid++] = pair(in - EPS + 2*PI, 1);
      //ev[eid++] = pair(out + EPS + 2*PI, -1);
      if (dist > d + EPS) {
        ld diff = asin(d / dist);
        out = angle + diff;
        in = angle + PI - diff;
        //ev.emplace_back(in - EPS, 1);
        //ev.emplace_back(out + EPS, -1);
        //ev.emplace_back(in - EPS + 2*PI, 1);
        //ev.emplace_back(out + EPS + 2*PI, -1);
        ev[eid++] = pair(in - EPS, 1);
        ev[eid++] = pair(out + EPS, -1);
        //ev[eid++] = pair(in - EPS + 2*PI, 1);
        //ev[eid++] = pair(out + EPS + 2*PI, -1);
      }
    }
    //sort(begin(ev), end(ev));
    sort(ev, ev + eid);

    int res = 0;
    int cur = 0;
    //for(auto [_, t] : ev) {
    for(int i=0; i<eid; i++) {
      //cur += t;
      cur += ev[i].second;
      res = max(res, cur);
    }

    ans = max(ans, res + 1);
  }

  cout << ans << nl;

  return 0;
}
