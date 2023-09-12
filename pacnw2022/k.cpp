#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct Int {
  int val;
  Int(int v = 0): val(v) {}
  void operator+=(const Int& o) {
    val += o.val;
    if(val >= MOD) val -= MOD;
  }
  friend ostream& operator<<(ostream& os, const Int& v) {
    return os << v.val;
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector g(n, vector(n, '?'));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
    }
  }

  // dp [mask] [last is I?] [done?]
  vector dp(1<<(n+1), array<array<Int, 2>, 2>());
  dp[0][0][0] = 1;
  for(int j=m-1; j>=0; j--) {
    for(int i=0; i<n; i++) {
      vector ndp(1<<(n+1), array<array<Int, 2>, 2>());
      for(int bm=0; bm<1<<(n+1); bm++) {
        if(g[i][j] == 'I' or g[i][j] == '?') {
          for(int done=0; done<2; done++) {
            ndp[bm>>1][1][done] += dp[bm][0][done];
            ndp[bm>>1][1][done] += dp[bm][1][done];
          }
        }
        if(g[i][j] == 'C' or g[i][j] == '?') {
          for(int done=0; done<2; done++) {
            ndp[bm>>1 | 1<<n][0][done] += dp[bm][0][done];
            ndp[bm>>1 | 1<<n][0][done] += dp[bm][1][done];
          }
        }
        if(g[i][j] == 'P' or g[i][j] == '?') {
          for(int done=0; done<2; done++) {
            ndp[bm>>1][0][done] += dp[bm][0][done];
            ndp[bm>>1][0][done] += dp[bm][1][done];
          }
          if(i != 0 and not (bm & 1<<n) and (bm & 0b11) == 0b11) {
            ndp[bm>>1][0][true] += dp[bm][1][false];
            ndp[bm>>1][0][false] += MOD - dp[bm][1][false].val;
          }
        }
      }
      dp = move(ndp);
    }
  }

  Int ans = 0;
  for(const auto& it : dp) {
    ans += it[0][true];
    ans += it[1][true];
  }
  cout << ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
