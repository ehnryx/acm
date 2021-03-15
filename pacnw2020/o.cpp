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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll solve(const string& s) {
  int n = s.size();

  vector dp(10, vector(2, vector<ll>(2))); // last digit, follow, zero
  dp[0][1][1] = true;
  for(int i=0; i<n; i++) {
    vector ndp(10, vector(2, vector<ll>(2))); // last digit, follow, zero
    ndp[0][0][1] += dp[0][0][1] + dp[0][1][1];
    for(int d=0; d<10; d++) {
      for(int c=0; c<10; c++) {
        if(d == c) continue;
        ndp[c][0][0] += dp[d][0][0] + dp[d][0][1];
        if((i > 0 && d == s[i-1] - '0') || (i == 0 && d == 0)) {
          if(c == s[i] - '0') {
            ndp[c][1][0] += dp[d][1][0] + dp[d][1][1];
          } else if(c < s[i] - '0') {
            ndp[c][0][0] += dp[d][1][0] + dp[d][1][1];
          }
        }
      }
    }
    for(int d=0; d<10; d++) {
      for(int f=0; f<2; f++) {
        for(int z=0; z<2; z++) {
          ndp[d][f][z] %= MOD;
        }
      }
    }
    dp = move(ndp);
  }

  ll res = 0;
  for(int d=0; d<10; d++) {
    res += dp[d][0][0] + dp[d][1][0];
  }
  return res % MOD;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  string l, r;
  cin >> l >> r;
  bool ok = true;
  for(int i=1; i<l.size(); i++) {
    ok &= (l[i] != l[i-1]);
  }
  cout << (solve(r) + MOD - solve(l) + ok) % MOD << nl;

  return 0;
}
