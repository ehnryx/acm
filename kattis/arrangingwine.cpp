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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll modpow(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2, n = n*n % m) {
    if(e&1) r = r*n % m;
  }
  return r;
}

ll inverse(ll n) {
  return modpow(n, MOD-2, MOD);
}

const int N = 2e6 + 7;
ll f[N], invf[N];

ll choose(int n, int r) {
  if(r<0 || r>n) return 0;
  return f[n] * invf[r] % MOD * invf[n-r] % MOD;
}

ll rising(int n, int r) {
  if(n == 0) return 0;
  return f[n+r-1] * invf[n-1] % MOD;
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

  f[0] = 1;
  for(int i=1; i<N; i++) {
    f[i] = f[i-1] * i % MOD;
  }
  invf[N-1] = inverse(f[N-1]);
  for(int i=N-2; i>=0; i--) {
    invf[i] = invf[i+1] * (i+1) % MOD;
  }

  int r, w, d;
  cin >> r >> w >> d;
  // [z^r] A(z)^{w+1}
  // where A(z) = 1 + z + ... + z^d

  vector<ll> top(r+1);
  for(int k=0; k*(d+1)<=r; k++) {
    int s = (k % 2 ? MOD-1 : 1);
    top[k*(d+1)] = s * choose(w+1, k) % MOD;
  }

  ll ans = 0;
  for(int k=0; k<=r; k++) {
    ll bot = rising(w+1, k) * invf[k] % MOD;
    ans = (ans + bot * top[r-k]) % MOD;
  }
  cout << ans << nl;

  return 0;
}
