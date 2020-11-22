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

int sqr(int x) {
  return x*x;
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
  vector<tuple<int,int,int,int>> v;
  for(int i=0; i<m; i++) {
    int j, x, y, t;
    cin >> j >> x >> y >> t;
    v.emplace_back(t, x, y, j);
  }
  sort(v.begin(), v.end());

  set<pair<int,int>> all;
  const int R = 1e6;
  for(int i=0; i<m; i++) {
    for(int j=0; j<5 && i+j<m; j++) {
      const auto& [ti, xi, yi, id] = v[i];
      const auto& [tj, xj, yj, jd] = v[i+j];
      if(id == jd) continue;
      if(sqr(xi-xj) + sqr(yi-yj) <= R && tj-ti <= 10) {
        all.insert(make_pair(min(id, jd), max(id, jd)));
      }
    }
  }

  cout << all.size() << nl;
  for(auto [a, b] : all) {
    cout << a << " " << b << nl;
  }

  return 0;
}
