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
constexpr ll MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

ll modpow(ll n, ll e, ll m = MOD) {
  ll r = 1;
  for(;e;e/=2, n = n*n % m) {
    if(e&1) r = r*n % m;
  }
  return r;
}

ll add(ll a, ll b) {
  return a + b < MOD ? a + b : a + b - MOD;
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

  const ll inv2 = modpow(2, MOD - 2);

  int n;
  cin >> n;
  vector<int> a(n), twos(n);
  ll cur = 0;
  for(int i=0; i<n; i++) {
    cin >> a[i];
    twos[i] = (a[i] == 2);
    if(i > 0) twos[i] += twos[i-1];
    if(a[i] == 3) {
      cur = add(cur, modpow(2, twos[i]));
    }
  }

  ll ans = 0;
  for(int i=0, ones=0; i<n; i++) {
    if(a[i] == 1) {
      ans = add(ans, cur);
      ones++;
    } else if(a[i] == 2) {
      cur = cur * inv2 % MOD;
    } else {
      cur = add(cur, MOD - 1);
      ans = add(ans, MOD - ones);
    }
  }
  cout << ans << nl;

  return 0;
}
