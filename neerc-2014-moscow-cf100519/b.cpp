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

ld get_sum(const vector<pair<int,ld>>& x, const vector<ld>& s, int l, int r) {
  int ri = upper_bound(x.begin(), x.end(), make_pair(r, (ld)INF)) - x.begin();
  int li = lower_bound(x.begin(), x.end(), make_pair(l, (ld)-INF)) - x.begin();
  return s[ri] - s[li];
}

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
  vector<tuple<int,int,int,int>> rects;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    rects.emplace_back(a, b, x, y);
  }
  map<int,ld> xvals, yvals;
  for(int i=0; i<m; i++) {
    int x, y, a, b;
    cin >> x >> y >> a >> b;
    if(!xvals.count(x)) xvals[x] = 1;
    xvals[x] *= (1 - (ld)b/100);
    if(!yvals.count(y)) yvals[y] = 1;
    yvals[y] *= (1 - (ld)a/100);
  }

  vector<pair<int,ld>> xv, yv;
  for(const auto& [x, p] : xvals) {
    xv.emplace_back(x, 1-p);
  }
  for(const auto& [y, p] : yvals) {
    yv.emplace_back(y, 1-p);
  }

  vector<ld> xpref(1, 0), ypref(1, 0);
  for(int i=0; i<xv.size(); i++) {
    xpref.push_back(xpref[i] + xv[i].second);
  }
  for(int i=0; i<yv.size(); i++) {
    ypref.push_back(ypref[i] + yv[i].second);
  }

  ld ans = 0;
  for(const auto& [a, b, x, y] : rects) {
    ld h = get_sum(xv, xpref, a, x);
    ld v = get_sum(yv, ypref, b, y);
    ans += h*(y-b+1) + v*(x-a+1) - h*v;
  }
  cout << ans << nl;

  return 0;
}
