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
const ll MOD = 1e9 + 7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<19;
ll fact[N], invf[N];

ll power(ll n, ll e) {
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

ll choose(int n, int r) {
  if(r < 0 || r > n) return 0;
  return fact[n] * invf[r] % MOD * invf[n-r] % MOD;
}

void init() {
  fact[0] = invf[0] = 1;
  for(int i=1; i<N; i++) {
    fact[i] = i * fact[i-1] % MOD;
    invf[i] = inverse(fact[i]);
  }
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

  init();

  int n;
  cin >> n;
  int m = 1<<n;
  vector<int> a(m+1);
  for(int i=1; i<=m; i++) {
    cin >> a[i];
  }

  vector inner(n, vector<ll>(m+2));
  for(int k=0; k<n; k++) {
    for(int j=m; j>0; j--) {
      ll cur = a[j] * choose((1<<n) - j, (1<<k) - 1) % MOD;
      inner[k][j] = (inner[k][j+1] + cur) % MOD;
      //cerr << "inner " << k << " " << j << " -> " << inner[k][j] << ", cur = " << cur << nl;
    }
  }
  //cerr << nl;

  ll sum = 0;
  for(int k=0; k<n; k++) {
    ll denom = choose((1<<n) - 2, (1<<k) - 1) * choose((1<<n) - 1 - (1<<k), (1<<k) - 1) % MOD;
    denom = inverse(denom * ((1<<n) - 1) % MOD);
    ll outer = (1<<k) * denom % MOD;
    for(int i=1; i<=m; i++) {
      ll cur = a[i] * choose((1<<n) - i - (1<<k), (1<<k) - 1) % MOD;
      cur = cur * outer % MOD * inner[k][i+1] % MOD;
      sum += cur;
    }
  }

  ll ans = (sum % MOD + MOD) % MOD;
  cout << ans << nl;

  return 0;
}
