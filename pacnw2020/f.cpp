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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Totient {
  const int N = 1e6 + 7;
  vector<int> ps; bool isc[N]; int f[N], e[N];
  void sieve() { f[1] = 1;
    for (int i = 2; i < N; i++) { if (!isc[i]) {
        ps.push_back(i); f[i] = i-1; e[i] = 1; } // f(p) for prime p
      for (int ip, j = 0; j < ps.size() && (ip=i*ps[j]) < N; j++) {
        isc[ip] = 1;
        if (i % ps[j] == 0) {
          f[ip] = f[i] * ps[j]; // f(ip) = f(i/p**e[i])f(p**(e[i]+1))
          e[ip] = e[i] + 1; break;
        } else { f[ip] = f[i] * f[ps[j]]; e[ip] = 1; } // f(ip)=f(i)f(p)
      } } }
}

ll power(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % m;
    n = n*n % m;
  }
  return r;
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

  Totient::sieve();

  int n, m;
  cin >> n >> m;

  vector<int> div;
  for(int i=2; i*i<=n; i++) {
    if(n % i == 0) {
      div.push_back(i);
      if(i*i < n) {
        div.push_back(n/i);
      }
    }
  }
  sort(div.begin(), div.end());

  ll ans = 0;
  for(int d : div) {
    int len = n/d;
    ll cnt = (power(2, len-1, m) + m - 1) % m;
    ll add = cnt * Totient::f[d] % m * (n-2) % m;
    ans = (ans + add) % m;
  }
  cout << ans << nl;

  return 0;
}
