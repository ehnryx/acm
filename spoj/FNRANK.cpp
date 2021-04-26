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

namespace sieve {
const int N = 1e5 + 1;
vector<int> ps; bool isc[N]; int f[N], e[N];
void sieve() { f[1] = 1;
  for (int i = 2; i < N; i++) { if (!isc[i]) {
      ps.push_back(i); f[i] = -1; e[i] = 1; } // f(p) for prime p
    for (int ip, j = 0; j < ps.size() && (ip=i*ps[j]) < N; j++) {
      isc[ip] = 1;
      if (i % ps[j] == 0) {
        f[ip] = 0; // f(ip) = f(i/p**e[i])f(p**(e[i]+1))
        e[ip] = e[i] + 1; break;
      } else { f[ip] = f[i] * f[ps[j]]; e[ip] = 1; } // f(ip)=f(i)f(p)
    } } }
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

  sieve::sieve();

  int T;
  cin >> T;
  while(T--) {
    int n, a, b;
    cin >> n >> a >> b;
    ll ans = 0;
    for(int f=1; f<=n; f++) {
      if(!sieve::f[f]) continue;
      for(int d=1; f*d<=n; d++) {
        ans += sieve::f[f] * ((ll)a*d/b + 1);
      }
    }
    cout << ans << nl;
  }

  return 0;
}
