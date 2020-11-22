//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld PI = acos((ld)-1);

pair<pt, pt> circle_tangent(ld r1, ld r2, ld d, int k) { // use below fn
  ld dr = (k & 2) ? (-r1-r2) : (r2-r1); ld t = asin(dr / d);
  pt p1=polar(r1, PI/2+t), p2=polar(r2, PI/2+t); if(k&2) p2*=-1;
  p2+=pt(d,0);
  if(k&1){ p1=pt(p1.real(),-p1.imag()); p2=pt(p2.real(),-p2.imag()); }
  return make_pair(p1, p2); }
pair<pt, pt> circle_tangent(pt p1, ld r1, pt p2, ld r2, int k) {
  // translate/rotate so c1 at (0,0), c2 at x-axis
  pt d = p2-p1; auto p = circle_tangent(r1,r2,abs(d),k); d /= abs(d);
  p.first *= d; p.second *= d; p.first += p1; p.second += p1; return p;}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int x, y, r;
  cin >> x >> y;
  pt s(x, y);
  cin >> x >> y;
  pt t(x, y);
  cin >> x >> y >> r;
  cin >> x >> y >> r;
  pt c(x, y);

  ld ans = 1e18;
  for(int i=0; i<2; i++) {
    pt a = circle_tangent(s, 0, c, r, i).second;
    for(int j=0; j<2; j++) {
      pt b = circle_tangent(t, 0, c, r, j).second;
      ld d = abs(a - s) + abs(b - t) + abs(arg((a - c) / (b - c))) * r;
      ans = min(ans, d);
    }
  }
  cout << ans << nl;

  return 0;
}
