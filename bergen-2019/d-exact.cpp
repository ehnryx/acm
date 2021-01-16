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
const ld EPS = 1e-12;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Point {
  ll x, y;
  Point(ld _x, ld _y): x(llround(_x * 1e6)), y(llround(_y * 1e6)) {}
  Point(ll _x, ll _y): x(_x), y(_y) {}
  bool operator == (const Point& o) const { return x == o.x && y == o.y; }
  Point operator - (const Point& o) const { return Point(x-o.x, y-o.y); }
  __int128 operator * (const Point& o) const { return (__int128)x*o.y - (__int128)y*o.x; }
  pt to_pt() const { return pt((ld)x/1e6, (ld)y/1e6); }
};

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

  int n, m;
  cin >> n >> m;
  vector<Point> p;
  for(int i=0; i<n; i++) {
    ld x, y;
    cin >> x >> y;
    Point cur(x, y);
    while((!p.empty() && p.back() == cur) ||
        (p.size() >= 2 && (cur - p.back()) * (p.back() - p[p.size()-2]) == 0)) {
      p.pop_back();
    }
    if(!p.empty()) assert(abs(p.back().to_pt() - pt(x, y)) > EPS);
    if(p.size() >= 2) assert(abs(arg((pt(x, y) - p.back().to_pt()) / (p.back().to_pt() - p[p.size()-2].to_pt()))) > EPS);
    p.push_back(cur);
  }
  reverse(p.begin(), p.end());

  vector<pt> v;
  transform(p.begin(), p.end(), back_inserter(v), [](const Point& x) {
    return x.to_pt();
  });
  n = v.size();
  //assert(n >= 2);

  vector<ld> dist(2*n);
  for(int i=1; i<n; i++) {
    dist[2*i+1] = dist[2*i] = dist[2*i-1] + abs(v[i] - v[i-1]);
  }

  vector<ld> lim(n, 180);
  for(int i=1; i<n-1; i++) {
    pt aft = (v[i+1] - v[i]) / abs(v[i+1] - v[i]);
    pt pre = (v[i] - v[i-1]) / abs(v[i] - v[i-1]);
    ld ang = (ld) 180 * abs(arg(aft / pre)) / M_PIl;
    lim[i] = 180 - ang;
  }

  vector<vector<ld>> dp(2*n, vector<ld>(m+1, 1e19));
  fill(dp[0].begin(), dp[0].end(), 0);
  for(int i=1; i<2*n; i++) {
    ld cmin = 180;
    for(int j=i-1; j>=0; j--) {
      if(j % 2 == 0) {
        cmin = min(cmin, lim[j/2]);
      }
      ld len = dist[i] - dist[j];
      for(int k=1; k<=m; k++) {
        dp[i][k] = min(dp[i][k], dp[j][k-1] + len / cmin);
      }
    }
    for(int k=0; k<=m; k++) {
      //cerr << "dp " << i << " " << k << " -> " << dp[i][k] << nl;
    }
  }
  cout << dp[2*n-3][m] + (dist[2*n-1] - dist[2*n-3]) / 180 << nl;

  return 0;
}
