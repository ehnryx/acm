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
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using vl = vector<ll>;

ll modpow(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2, n = n * n % m) {
    if(e&1) r = r * n % m;
  }
  return r;
}

const ll mod = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<ll> vl;
void ntt(vl& a, vl& rt, vl& rev, int n) {
  for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) for (int j = 0; j < k; j++) {
				ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
				a[i + j + k] = (z > ai ? ai - z + mod : ai - z);
				ai += (ai + z >= mod ? z - mod : z);
	}
}

vl conv(const vl& a, const vl& b) {
	if (a.empty() || b.empty()) return {};
	int s = a.size()+b.size()-1, B = 32 - __builtin_clz(s), n = 1 << B;
	vl L(a), R(b), out(n), rt(n, 1), rev(n);
	L.resize(n), R.resize(n);
  for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << B) / 2;
	ll curL = mod / 2, inv = modpow(n, mod - 2, mod);
	for (int k = 2; k < n; k *= 2) {
		ll z[] = {1, modpow(root, curL /= 2, mod)};
    for (int i = k; i < 2*k; i++) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	ntt(L, rt, rev, n); ntt(R, rt, rev, n);
  for (int i=0;i<n;i++) out[-i & (n-1)] = L[i] * R[i] % mod * inv % mod;
	ntt(out, rt, rev, n);
	return {out.begin(), out.begin() + s};
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

  int n, k;
  cin >> n >> k;

  vector<ll> a(k+1), b(k+1);
  vector<ll> f(k+1), invf(k+1);
  f[0] = 1;
  for(int i=0; i<=k; i++) {
    invf[i] = modpow(f[i], MOD - 2, MOD);
    int s = i % 2 ? -1 : 1;
    a[i] = invf[i] * s;
    b[i] = modpow(i, k, MOD) * invf[i] % MOD;
    if(i+1 <= k) {
      f[i+1] = f[i] * (i + 1) % MOD;
    }
  }
  vector<ll> stirling = conv(a, b);

  ll ans = 0;
  ll prod = 1;
  for(int i=1; i<=k; i++) {
    prod = prod * (n - i + 1) % MOD;
    ans += stirling[i] * prod % MOD * modpow(n + 1, n - i, MOD) % MOD;
  }
  ans = (ans % MOD + MOD) % MOD;
  cout << ans << nl;

  return 0;
}
