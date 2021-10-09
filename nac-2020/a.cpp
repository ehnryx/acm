//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const ll MOD = 998244353;

const int N = 1e6 + 3;

int ps[N]; bool isc[N]; int f[N], e[N];
void sieve() {
  int pid = 0;
  f[1] = 1;
  for(int i=2; i<N; i++) {
    if(!isc[i]) {
      ps[pid++] = i;
      f[i] = -1;
      e[i] = 1;
    }
    for(int ip, j = 0; j < pid && (ip=i*ps[j]) < N; j++) {
      isc[ip] = 1;
      if(i % ps[j] == 0) {
        f[ip] = 0;
        e[ip] = e[i] + 1;
        break;
      } else {
        f[ip] = f[i] * f[ps[j]];
        e[ip] = 1;
      }
    }
  }
}

ll power(ll n, ll x) {
  ll r = 1;
  for(;x>0;x/=2) {
    if(x&1) r = r*n % MOD;
    n = n*n % MOD;
  }
  return r;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  sieve();

  int m, k;
  cin >> m >> k;

  ll ans = 0;
  int sum = 0;
  for(int d=1; d<=k; d++) {
    ll cnt = power(2*(k/d) + 1, m);
    ans += cnt * f[d];
    sum += f[d];
  }
  ans = (ans % MOD + MOD) % MOD;
  ans = (ans + MOD - sum + 1) % MOD;
  cout << ans << nl;

  return 0;
}
