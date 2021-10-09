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
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e6 + 7;
ll dp[N][4][2]; // [none, 1, 0, 0] x [follow]

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string s;
  cin >> s;
  int n = s.size();
  dp[0][0][1] = 1;
  for(int i=1; i<=n; i++) {
    if(s[i-1] == '1') {
      dp[i][1][1] = dp[i-1][0][1] + dp[i-1][1][1];
      dp[i][2][1] = dp[i-1][2][1];
      dp[i][3][1] = dp[i-1][3][1];
    } else if(s[i-1] == '0') {
      dp[i][0][1] = dp[i-1][0][1];
      dp[i][2][1] = dp[i-1][1][1];
      dp[i][3][1] = dp[i-1][2][1] + dp[i-1][3][1];
    } else {
      for(int j=0; j<4; j++) {
        dp[i][j][1] = dp[i-1][j][1];
      }
    }
    assert(dp[i][0][1] + dp[i][1][1] + dp[i][2][1] + dp[i][3][1] == 1);

    for(int d=0; d<10; d++) {
      if(d == 1) {
        dp[i][1][0] += dp[i-1][0][0] + dp[i-1][1][0];
        dp[i][2][0] += dp[i-1][2][0];
        dp[i][3][0] += dp[i-1][3][0];
      } else if(d == 0) {
        dp[i][0][0] += dp[i-1][0][0];
        dp[i][2][0] += dp[i-1][1][0];
        dp[i][3][0] += dp[i-1][2][0] + dp[i-1][3][0];
      } else {
        for(int j=0; j<4; j++) {
          dp[i][j][0] += dp[i-1][j][0];
        }
      }
      if(d < s[i-1]-'0') {
        if(d == 1) {
          dp[i][1][0] += dp[i-1][0][1] + dp[i-1][1][1];
          dp[i][2][0] += dp[i-1][2][1];
          dp[i][3][0] += dp[i-1][3][1];
        } else if(d == 0) {
          dp[i][0][0] += dp[i-1][0][1];
          dp[i][2][0] += dp[i-1][1][1];
          dp[i][3][0] += dp[i-1][2][1] + dp[i-1][3][1];
        } else {
          for(int j=0; j<4; j++) {
            dp[i][j][0] += dp[i-1][j][1];
          }
        }
      }
    }

    for(int j=0; j<4; j++) {
      dp[i][j][0] %= MOD;
    }
  }

  ll ans = (dp[n][2][0] + dp[n][2][1]) % MOD;
  cout << ans << nl;

  return 0;
}
