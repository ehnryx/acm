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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<int> a(n), b(n), c(n);
    map<int,int> remap;
    for(int i=0; i<n; i++) {
      cin >> a[i] >> b[i] >> c[i];
      remap[a[i]];
    }

    int rid = 1;
    for(auto& it : remap) {
      it.second = rid++;
    }

    for(int i=0; i<n; i++) {
      a[i] = remap[a[i]];
      b[i] = prev(remap.upper_bound(b[i]))->second;
    }

    vector dp(rid+1, vector<int>(rid+1));
    for(int d=0; d<rid; d++) {
      for(int i=1; i+d<rid; i++) {
        tuple<int,int,int> high(0, 0, 0);
        for(int j=0; j<n; j++) {
          if(i <= a[j] && b[j] <= i+d) {
            high = max(high, make_tuple(c[j], a[j], b[j]));
          }
        }
        auto [v, l, r] = high;
        if(v > 0) {
          dp[i][i+d] = INF;
          for(int j=l; j<=r; j++) {
            dp[i][i+d] = min(dp[i][i+d], v + dp[i][j-1] + dp[j+1][i+d]);
          }
        }
      }
    }
    cout << dp[1][rid-1] << nl;
  }

  return 0;
}
