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



// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  int v[n+1], p[n+1];
  int sum = 0;
  for(int i=1; i<=n; i++) {
    cin >> v[i] >> p[i];
    sum += p[i];
  }

  ll dp[5000+1];
  memset(dp, INF, sizeof dp);
  dp[0] = 0;
  for(int i=1; i<=n; i++) {
    int cost = (v[i]+2) / 2;
    for(int j=sum; j>=0; j--) {
      if(j >= p[i]) {
        dp[j] = min(dp[j], dp[j-p[i]] + cost);
      }
    }
  }

  ll ans = INFLL;
  for(int i=0; i<=sum; i++) {
    if(2*i > sum) {
      ans = min(ans, dp[i]);
    }
  }
  cout << ans << nl;

  return 0;
}
