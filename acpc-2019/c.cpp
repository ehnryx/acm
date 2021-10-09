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

ll mpow(ll n, ll e) {
  ll res = 1;
  for(;e;e/=2) {
    if(e&1) res = res*n % MOD;
    n = n*n % MOD;
  }
  return res;
}

const int N = 1e5+1;
ll fact[N], invf[N];

ll ncr(ll n, ll r) {
  if(r<0 || r>n) return 0;
  return fact[n] * invf[r] % MOD * invf[n-r] % MOD;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  fact[0] = invf[0] = 1;
  for (int i=1;i<N;i++) {
    fact[i] = fact[i-1] * i % MOD;
    invf[i] = mpow(fact[i], MOD-2);
  }

  int n,k,m;
  cin >> m >> k >> n;

  ll tot = mpow(ncr(n,m), k);
  for (int i=1;i<=m;i++) {
    int s = (i%2 ? -1 : 1);
    ll cur = ncr(n,i) * mpow(ncr(n-i,m-i), k) % MOD;
    tot += s * cur;
  }
  tot = (tot % MOD + MOD) % MOD;
  cout << tot << nl;

  return 0;
}
