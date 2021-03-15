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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e6 + 1;
vector<int> ps; bool isc[N]; int f[N], d[N], e[N];
void sieve() { f[1] = 1, d[1] = 0;
  for (int i = 2; i < N; i++) { if (!isc[i]) {
      ps.push_back(i); f[i] = 2; d[i] = 1; e[i] = 1; } // f(p) for prime p
    for (int ip, j = 0; j < ps.size() && (ip=i*ps[j]) < N; j++) {
      isc[ip] = 1;
      if (i % ps[j] == 0) {
        d[ip] = d[i];
        f[ip] = f[i]/(e[i]+1) * (e[i]+2); // f(ip) = f(i/p**e[i])f(p**(e[i]+1))
        e[ip] = e[i] + 1; break;
      } else {
        f[ip] = f[i] * f[ps[j]];
        d[ip] = d[i] + d[ps[j]];
        e[ip] = 1;
      } // f(ip)=f(i)f(p)
    } } }

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

  sieve();
  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    int v;
    cin >> v;
    cout << f[v] - d[v] << nl;
  }

  return 0;
}
