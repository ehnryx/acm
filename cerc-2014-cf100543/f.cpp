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
const ll MOD = 1e9 + 9;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll ncr(int n, int r) {
  if(r < 0 || r > n) return 0;
  ll res = 1;
  for(int i=0; i<r; i++) {
    res *= n-i;
  }
  for(int i=1; i<=r; i++) {
    res /= i;
  }
  return res;
}

int before(int c) {
  assert(isalpha(c) || c == 0);
  return c ? c-'a' : 0;
}

int after(int c) {
  assert(isalpha(c) || c == 0);
  return c ? 'z'-c : 26;
}

int between(int a, int b) {
  assert(isalpha(a) || a == 0);
  assert(isalpha(b) || b == 0);
  if(!a) return before(b);
  if(!b) return 0;
  return max(0, b - a - 1);
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

  int T;
  cin >> T;
  while(T--) {
    vector<string> s(3);
    for(int i=0; i<3; i++) {
      cin >> s[i];
    }

    int len = 0;
    for(int t=0; t<3; t++) {
      len = max(len, (int)s[t].size());
    }
    for(int t=0; t<3; t++) {
      s[t].resize(len, 0);
    }

    const string& a = s[0];
    const string& b = s[1];
    const string& c = s[2];

    // same, tops, bots, none
    vector<ll> dp(4);
    dp[0] = 1;
    for(int i=0; i<len; i++) {
      int bm = (a[i] == '?') << 2 | (b[i] == '?') << 1 | (c[i] == '?');
      vector<ll> ndp(4);
      if(bm == 0b000) {
        if(a[i] == b[i] && b[i] == c[i]) {
          ndp = dp;
        } else if(a[i] == b[i]) {
          ndp[1] = dp[1] + (b[i] < c[i] ? dp[0] : 0);
          ndp[3] = dp[3] + (b[i] < c[i] ? dp[2] : 0);
        } else if(b[i] == c[i]) {
          ndp[2] = dp[2] + (a[i] < b[i] ? dp[0] : 0);
          ndp[3] = dp[3] + (a[i] < b[i] ? dp[1] : 0);
        } else {
          ndp[3] = dp[3]
            + (a[i] < b[i] ? dp[1] : 0)
            + (b[i] < c[i] ? dp[2] : 0)
            + (a[i] < b[i] && b[i] < c[i] ? dp[0] : 0);
        }
      } else if(bm == 0b100) {
        if(b[i] == c[i]) {
          ndp[0] = dp[0];
          ndp[1] = dp[1];
          ndp[2] = 26 * dp[2] + before(b[i]) * dp[0];
          ndp[3] = 26 * dp[3] + before(b[i]) * dp[1];
        } else {
          ndp[1] = dp[1] + (b[i] < c[i] ? dp[0] : 0);
          ndp[3] = 26 * dp[3]
            + before(b[i]) * dp[1]
            + 26 * (b[i] < c[i] ? dp[2] : 0)
            + before(b[i]) * (b[i] < c[i] ? dp[0] : 0);
        }
      } else if(bm == 0b001) {
        if(a[i] == b[i]) {
          ndp[0] = dp[0];
          ndp[1] = 26 * dp[1] + after(b[i]) * dp[0];
          ndp[2] = dp[2];
          ndp[3] = 26 * dp[3] + after(b[i]) * dp[2];
        } else {
          ndp[2] = dp[2] + (a[i] < b[i] ? dp[0] : 0);
          ndp[3] = 26 * dp[3]
            + after(b[i]) * dp[2]
            + 26 * (a[i] < b[i] ? dp[1] : 0)
            + after(b[i]) * (a[i] < b[i] ? dp[0] : 0);
        }
      } else if(bm == 0b010) {
        if(a[i] == c[i]) {
          ndp[0] = dp[0];
          ndp[1] = dp[1];
          ndp[2] = dp[2];
          ndp[3] = 26 * dp[3]
            + after(a[i]) * dp[1]
            + before(c[i]) * dp[2];
        } else {
          ndp[1] = dp[1] + (a[i] < c[i] ? dp[0] : 0);
          ndp[2] = dp[2] + (a[i] < c[i] ? dp[0] : 0);
          ndp[3] = 26 * dp[3]
            + after(a[i]) * dp[1]
            + before(c[i]) * dp[2]
            + between(a[i], c[i]) * dp[0];
        }
      } else if(bm == 0b111) {
        ndp[0] = 26 * dp[0];
        ndp[1] = 26 * 26 * dp[1] + ncr(26, 2) * dp[0];
        ndp[2] = 26 * 26 * dp[2] + ncr(26, 2) * dp[0];
        ndp[3] = 26 * 26 * 26 * dp[3]
          + 26 * ncr(26, 2) * dp[2]
          + 26 * ncr(26, 2) * dp[1]
          + ncr(26, 3) * dp[0];
      } else if(bm == 0b011) {
        ndp[0] = dp[0];
        ndp[1] = 26 * dp[1] + after(a[i]) * dp[0];
        ndp[2] = 26 * dp[2] + after(a[i]) * dp[0];
        ndp[3] = 26 * 26 * dp[3]
          + 26 * after(a[i]) * dp[1]
          + ncr(26, 2) * dp[2]
          + ncr(after(a[i]), 2) * dp[0];
      } else if(bm == 0b110) {
        ndp[0] = dp[0];
        ndp[1] = 26 * dp[1] + before(c[i]) * dp[0];
        ndp[2] = 26 * dp[2] + before(c[i]) * dp[0];
        ndp[3] = 26 * 26 * dp[3]
          + 26 * before(c[i]) * dp[2]
          + ncr(26, 2) * dp[1]
          + ncr(before(c[i]), 2) * dp[0];
      } else if(bm == 0b101) {
        ndp[0] = dp[0];
        ndp[1] = 26 * dp[1] + after(b[i]) * dp[0];
        ndp[2] = 26 * dp[2] + before(b[i]) * dp[0];
        ndp[3] = 26 * 26 * dp[3]
          + 26 * before(b[i]) * dp[1]
          + 26 * after(b[i]) * dp[2]
          + before(b[i]) * after(b[i]) * dp[0];
      } else {
        assert(false);
      }

      for(int j=0; j<4; j++) {
        dp[j] = ndp[j] % MOD;
      }
    }

    cout << dp[3] << nl;
  }

  return 0;
}
