#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;

const int MOD = 1e6 + 3;
ll power(ll n, int e) {
  ll r = 1;
  for( ; e>0; e/=2) {
    if(e&1) r = r*n % MOD;
    n = n*n % MOD;
  }
  return r;
}
ll inverse(ll n) {
  return power(n, MOD-2);
}

const int N = 4e5 + 7;
ll l[N], t[N], S[N];
ll fact[N], invf[N];
ll inv[MOD];

ll ncr(int n, int r) {
  if(r<0 || r>n) return 0;
  return fact[n] * invf[r] % MOD * invf[n-r] % MOD;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  for(int i=1; i<MOD; i++) {
    inv[i] = inverse(i);
  }
  fact[0] = 1;
  for(int i=1; i<N; i++) {
    fact[i] = fact[i-1] * i % MOD;
    invf[i] = inv[fact[i]];
  }

  int n, a, b, c;
  cin >> n >> a >> b >> c;
  for(int i=1; i<=n; i++) {
    cin >> l[i];
  }
  for(int i=1; i<=n; i++) {
    cin >> t[i];
  }

  for(int j=0, k=0; j<=n-2; j++) {
    S[0] += ncr(k+j, k) * power(b, j) % MOD;
  }
  S[0] %= MOD;
  for(int k=1; k<=n-2; k++) {
    if(b != 1) {
      S[k] = (ncr(k+n-2, k) * power(b, n-1) + MOD - S[k-1]) % MOD;
      S[k] = S[k] * inv[(MOD+b-1)%MOD] % MOD;
    } else {
      S[k] = ncr(k+n-2+1, k+1);
    }
  }

  ll first = 0;
  ll second = 0;
  for(int k=0; k<=n-2; k++) {
    first += ncr(n-2+k, n-2) * power(b, k) % MOD * l[n-k] % MOD;
    second += ncr(n-2+k, n-2) * power(a, k) % MOD * t[n-k] % MOD;
  }
  first = first % MOD * power(a, n-1) % MOD;
  second = second % MOD * power(b, n-1) % MOD;

  ll third = 0;
  for(int k=0; k<=n-2; k++) {
    third += power(a, k) * S[k];
  }
  third = third % MOD * c % MOD;

  cout << (first + second + third) % MOD << nl;

  return 0;
}
