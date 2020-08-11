//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "false"

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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll mod_mul(ll a, ll b, ll m) {
  return (__int128)a*b % m;
}

ll mod_pow(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % m;
    n = n*n % m;
  }
  return r;
}

const ll wit[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
bool is_prime(ll n) { if (n<2) return 0; if (n%2 == 0) return n == 2;
  ll r = __builtin_ctzll(n-1), d = (n-1)>>r;
  for (ll a : wit) { a %= n; if (!a) return 1;
    if (a == 1 || a == n-1) continue;
    ll x = mod_pow(a,d,n), y;
    for (int i = 0; i < r; i++) { y = mod_mul(x,x,n);
      if (y == 1 && x != 1 && x != n-1) return 0; x = y; }
    if (x != 1) return 0; } return 1; }

ll get_factor(ll n) { if (n%2 == 0) return 2; if (is_prime(n)) return n;
  while (1) { ll x = rng()%(n-1)+1, c = rng()%(n-1)+1, y = 2, d = 1;
    // optimization: break when sz becomes too large
    for (int sz = 2; d == 1; sz *= 2) {
      for (int i = 0; i < sz && d <= 1; i++)
        x = (mod_mul(x,x,n)+c) % n, d = __gcd(abs(x-y), n);
    /* can replace above with the below to reduce # of gcd computations
      ll z = 1;
      for (int i = 0; i < sz && d <= 1; ) { ll px = x;
        for (int j = 0; i < sz && d <= 1 && j < 100; i++, j++)
          x = (mod_mul(x,x,n)+c)%n, z = mod_mul(z, x-y, n);
        z = abs(z); d = __gcd(z, n);
        if (d == n) { x = px, d = 1;
          for (int j = 0; d <= 1 && j < 100; j++)
            x = (mod_mul(x, x, n)+c)%n, d = __gcd(abs(x-y), n); } } */
      y = x; } if (d > 1 && d != n) return d; } }

ll solve(ll n) {
  ll orig = n;
  vector<pair<ll,int>> f;

  ll k = get_factor(n);
  while(!is_prime(k)) {
    k = get_factor(k);
  }
  int cnt = 0;
  while(n % k == 0) {
    n /= k;
    cnt++;
  }
  f.emplace_back(k, cnt);

  k = n;
  while(!is_prime(k)) {
    k = get_factor(k);
  }
  cnt = 0;
  while(n % k == 0) {
    n /= k;
    cnt++;
  }
  f.emplace_back(k, cnt);

  vector<ll> order;
  for(ll i=0, a=1; i<=f[0].second; i++, a*=f[0].first) {
    for(ll j=0, b=1; j<=f[1].second; j++, b*=f[1].first) {
      if(!i && !j || i==f[0].second && j==f[1].second) continue;
      order.push_back(a*b);
    }
  }
  sort(order.begin(), order.end());

  map<ll,ll> dp;
  dp[orig] = 1;
  for(ll v : order) {
    map<ll,ll> ndp = dp;
    for(const auto& [val, c] : dp) {
      for(ll x = val; x % v == 0; x /= v) {
        ndp[x/v] += c;
      }
    }
    dp = move(ndp);
  }
  return dp[1];
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

  ll n;
  cin >> n;
  cout << solve(n) << nl;

  return 0;
}
