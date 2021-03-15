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

ll power(ll n, int e) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % MOD;
    n = n*n % MOD;
  }
  return r;
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

  int n, r, c, k;
  cin >> n >> r >> c >> k;
  int m = max(r, c) + 1;

  vector<ll> f(m), fs(m);
  for(int i=0; i<m; i++) {
    f[i] = (power(1 + i, n) - power(i, n) + MOD) % MOD;
    fs[i] = f[i];
    if(i > 0) fs[i] = (fs[i] + fs[i-1]) % MOD;
  }

  ll ans = 0;
  for(int a=1; a<=r; a++) {
    int b = (k + a-1) / a;
    if(b > c) continue;
    ll cur = 0;
    for(int i=0; i+a<=r; i++) {
      cur = (cur + f[i] * f[r-a-i]) % MOD;
    }
    ll other = 0;
    for(int j=0; j+b<=c; j++) {
      other = (other + f[j] * fs[c-b-j]) % MOD;
    }
    ans = (ans + cur * other) % MOD;
  }
  cout << ans << nl;

  return 0;
}
