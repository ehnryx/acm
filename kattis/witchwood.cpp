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

  int n, m, k;
  cin >> n >> m >> k;
  vector<int> t(m);
  vector<ld> p(m);
  for(int i=0; i<m; i++) {
    cin >> t[i] >> p[i];
  }

  ld l = 0;
  ld r = 1e30;
  for(int bs=0; bs<120; bs++) {
    ld v = (l+r) / 2;
    vector<ld> dp(n+1);
    for(int i=1; i<=n; i++) {
      dp[i] = 1e30;
      for(int j=0; j<m; j++) {
        dp[i] = min(dp[i], t[j] + p[j]*(k+v) + (1-p[j])*dp[i-1]);
      }
    }
    if(dp[n] < v) {
      r = v;
    } else {
      l = v;
    }
  }
  cout << r << nl;

  return 0;
}
