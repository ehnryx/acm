//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "almost"

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

int dumb(int n) {
  int ans = 0;
  for(int k=1; k<=n; k++) {
    string s = to_string(k);
    int len = s.size();
    int bad = 0;
    for(int i=0; i<len/2; i++) {
      bad += s[i] != s[len-1-i];
    }
    ans += bad <= 1;
  }
  return ans;
}

const int N = 19;
ll pals[N];
ll dp[N][2][2][2]; // position, follow, smaller, used

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  for(int i=1; i<=18; i++) {
    pals[i] = 9;
    for(int j=1; j<(i+1)/2; j++) {
      pals[i] *= 10;
    }
  }

  for(ll num; cin >> num && num; ) {
    string s = to_string(num);
    int n = s.size();
    if(n == 1) {
      cout << num << nl;
      continue;
    }

    memset(dp, 0, sizeof dp);
    dp[0][1][1][0] = 1;
    for(int i=0; i<n/2; i++) {
      // put d
      for(int d=(i?0:1); d<10; d++) {
        // from smaller
        for(int ts=0; ts<2; ts++) {
          for(int us=0; us<2; us++) {
            dp[i+1][0][0][us] += dp[i][0][ts][us];
          }
        }
        // from follow
        if(d < s[i]-'0') {
          for(int ts=0; ts<2; ts++) {
            for(int us=0; us<2; us++) {
              dp[i+1][0][0][us] += dp[i][1][ts][us];
            }
          }
        } else if(d == s[i]-'0') {
          for(int us=0; us<2; us++) {
            if(d < s[n-1-i]-'0') {
              dp[i+1][1][1][us] += dp[i][1][1][us];
              dp[i+1][1][1][us] += dp[i][1][0][us];
            } else if(d > s[n-1-i]-'0') {
              dp[i+1][1][0][us] += dp[i][1][0][us];
              dp[i+1][1][0][us] += dp[i][1][1][us];
            } else {
              dp[i+1][1][0][us] += dp[i][1][0][us];
              dp[i+1][1][1][us] += dp[i][1][1][us];
            }
          }
        }

        // also put c
        for(int c=0; c<10; c++) {
          if(c == d) continue;
          // from smaller
          for(int ts=0; ts<2; ts++) {
            dp[i+1][0][0][1] += dp[i][0][ts][0];
          }
          // from follow
          if(d < s[i]-'0') {
            for(int ts=0; ts<2; ts++) {
              dp[i+1][0][0][1] += dp[i][1][ts][0];
            }
          } else if(d == s[i]-'0') {
            if(c < s[n-1-i]-'0') {
              dp[i+1][1][1][1] += dp[i][1][1][0];
              dp[i+1][1][1][1] += dp[i][1][0][0];
            } else if(c > s[n-1-i]-'0') {
              dp[i+1][1][0][1] += dp[i][1][0][0];
              dp[i+1][1][0][1] += dp[i][1][1][0];
            } else {
              dp[i+1][1][0][1] += dp[i][1][0][0];
              dp[i+1][1][1][1] += dp[i][1][1][0];
            }
          }
        }
      }
    }

    //cerr<<"no follow, unused -> "<<dp[n/2][0][0][0]<<nl;
    //cerr<<"no follow,   used -> "<<dp[n/2][0][0][1]<<nl;
    //cerr<<"   follow, unused -> "<<dp[n/2][1][1][0]<<nl;
    //cerr<<"   follow,   used -> "<<dp[n/2][1][1][1]<<nl;
    //cerr<<"oddfollow, unused -> "<<dp[n/2][1][0][0]<<nl;
    //cerr<<"oddfollow,   used -> "<<dp[n/2][1][0][1]<<nl;

    ll ans = (dp[n/2][0][0][0] + dp[n/2][0][0][1]) * (n % 2 ? 10 : 1);
    ll tight = dp[n/2][1][1][0] + dp[n/2][1][1][1];
    ans += (n % 2 ? tight * (s[n/2]-'0' + 1) : tight);
    if(n % 2) {
      //cerr<<" !! add odds"<<nl;
      ans += (dp[n/2][1][0][0] + dp[n/2][1][0][1]) * (s[n/2]-'0');
    }
    //cerr<<"ans: "<<ans<<nl;
    for(int i=1; i<n; i++) {
      ans += pals[i];
      if(i > 1) {
        ans += pals[i]; // last digit to 0
        ans += pals[i] * ((i/2-1)*9 + 8); // change half
      }
    }
    cout << ans << nl;

#ifndef ONLINE_JUDGE
    if(ans != dumb(num)) {
      cout << "BAD @ " << num << nl;
      cout << "GOT " << ans << " EXPECTED " << dumb(num) << nl;
      exit(-1);
    }
#endif
  }

  return 0;
}
