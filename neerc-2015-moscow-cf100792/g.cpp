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

  int n;
  cin >> n;
  vector<pair<pt,int>> v;
  pt init = exp(pt(0, PI/8));
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    v.emplace_back(pt(x, y) * init, i + 1);
  }

  pt step = exp(pt(0, PI/4));
  tuple<ld,int,int> ans(-1, -1, -1);
  for(int r=0; r<4; r++) {
    pair<ld,int> minx(INFLL, -1);
    pair<ld,int> maxx(-INFLL, -1);
    for(int i=0; i<n; i++) {
      v[i].first *= step;
      minx = min(minx, make_pair(v[i].first.real(), v[i].second));
      maxx = max(maxx, make_pair(v[i].first.real(), v[i].second));
    }
    ans = max(ans, make_tuple(maxx.first - minx.first, maxx.second, minx.second));
  }
  cout << get<1>(ans) << " " << get<2>(ans) << nl;

  return 0;
}
