#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const char nl = '\n';

ll power(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % m;
    n = n*n % m;
  }
  return r;
}

void add_to(int& a, int b, int m) {
  a += b;
  if(a >= m) a -= m;
}

const int N = 12;
int dp[N+1][1<<N], ndp[N+1][1<<N];

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m, mod;
  cin >> n >> m >> mod;

  if(n%2 == 1 && m%2 == 1) {
    cout << 1 << nl;
    return 0;
  }

  if(m%2 == 1) swap(n, m);
  if(n%2 == 1) {
    cout << power(m/2 + 1, n/2, mod) << nl;
    return 0;
  }

  n /= 2; // scary
  m /= 2; // sad

  memset(dp, 0, sizeof dp);
  dp[0][0] = 1;
  for(int i=1; i<=m; i++) {
    memset(ndp, 0, sizeof ndp);
    for(int j=0; j<=n; j++) {
      for(int k=0; k<=n; k++) {
        for(int bm=0; bm<1<<n; bm++) {
          int patched = bm;
          if(k+1 < j) {
            // replace 01 with 11 when k < j
            int window = bm >> k & ((1 << (j-k)) - 1);
            patched |= (window >> 1) << k;
          }
          if(k-1 > j) {
            // replace 10 with 11 when k > j
            int window = bm >> j & ((1 << (k-j)) - 1);
            patched |= ((window << j) << 1) & ~(1 << k);
          }
          // init sosdp
          add_to(ndp[j][patched], dp[k][bm], mod);
        }
      }
      // sosdp
      for(int k=0; k<n; k++) {
        for(int bm=0; bm<1<<n; bm++) {
          if(bm & 1<<k) {
            add_to(ndp[j][bm], ndp[j][bm ^ 1<<k], mod);
          }
        }
      }
    }

    swap(dp, ndp);
  }

  int ans = 0;
  for(int j=0; j<=n; j++) {
    for(int bm=0; bm<1<<n; bm++) {
      add_to(ans, dp[j][bm], mod);
    }
  }
  cout << ans << nl;

  return 0;
}
