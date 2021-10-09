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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e5+1;
int dsu[N];
int find(int i) {
  if(dsu[i] == -1) return i;
  return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
  if(find(i) != find(j)) {
    dsu[find(i)] = find(j);
  }
}

int sz[N], cnt[N];
ll fact[N], invf[N];
ll ncr(int n, int r) {
  if(r<0 || r>n) return 0;
  return fact[n] * invf[r] % MOD * invf[n-r] % MOD;
}
ll power(ll n, int e) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % MOD;
    n = n*n % MOD;
  }
  return r;
}
ll inverse(ll n) {
  return power(n, MOD-2);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  memset(dsu, -1, sizeof dsu);
  fact[0] = invf[0] = 1;
  for(int i=1; i<N; i++) {
    fact[i] = fact[i-1] * i % MOD;
    invf[i] = inverse(fact[i]);
  }

  int n;
  cin >> n;
  int a[n+1];
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    link(i, a[i]);
  }

  for(int i=1; i<=n; i++) {
    sz[find(i)]++;
  }

  for(int i=1; i<=n; i++) {
    if(find(i) == i) {
      cnt[sz[i]]++;
    }
  }

  ll ans = 1;
  for(int i=1; i<=n; i++) {
    if(i%2 == 1) {
      ll sum = 0;
      for(int j=0; 2*j<=cnt[i]; j++) {
        ll choose = ncr(cnt[i], 2*j) * ncr(2*j, j) % MOD;
        choose = choose * fact[j] % MOD * inverse(power(2, j)) % MOD;
        sum += choose * power(i, j) % MOD;
      }
      ans = ans * (sum % MOD) % MOD;
    } else if(cnt[i]%2 == 0) {
      ll cur = ncr(cnt[i], cnt[i]/2) * fact[cnt[i]/2] % MOD;
      cur = cur * inverse(power(2, cnt[i]/2)) % MOD * power(i, cnt[i]/2) % MOD;
      ans = ans * cur % MOD;
    } else {
      ans = 0;
    }
  }
  cout << ans << nl;

  return 0;
}
