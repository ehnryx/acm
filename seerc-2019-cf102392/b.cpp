//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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

const int N = 500 + 1;
ll dp[N][N], ndp[N][N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, a, b;
  cin >> n >> a >> b;

  vector<tuple<int,int,int,int>> vals;
  for(int i=0; i<n; i++) {
    int x, t, y, r;
    cin >> x >> t >> y >> r;
    vals.emplace_back(x, t, y, r);
  }
  sort(vals.begin(), vals.end());

  memset(dp, 0x3f, sizeof dp);
  dp[0][0] = 0;
  for(auto [x, t, y, r] : vals) {
    // skip
    for(int u=0; u<=a; u++) {
      for(int v=0; v<=b; v++) {
        ndp[u][v] = dp[u][v];
      }
    }

    // use
    for(int u=0; u<=a; u++) {
      for(int v=0; v<=b; v++) {
        int nu, nv;
        // use on first level
        if(u < a) {
          nu = min(a, u + x);
          nv = min(b, v + max(0, u+x-a));
          ndp[nu][nv] = min(ndp[nu][nv], dp[u][v] + t);
        }
        // use on second level
        if(v < b) {
          nu = u;
          nv = min(b, v + y);
          ndp[nu][nv] = min(ndp[nu][nv], dp[u][v] + r);
        }
      }
    }
    swap(dp, ndp);
  }

  if(dp[a][b] < INFLL) {
    cout << dp[a][b] << nl;
  } else {
    cout << -1 << nl;
  }

  return 0;
}
