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

  const int N = 2e7;
  bitset<N> np;
  np[0] = np[1] = true;
  for(int i=2; i*i<N; i++) {
    if(np[i]) continue;
    for(int j=i*i; j<N; j+=i) {
      np[j] = true;
    }
  }

  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    ld a, b;
    cin >> a >> b;
    ll x = llround(a * 1e5);
    ll y = llround(b * 1e5);
    ll g = __gcd(x, y);
    x /= g;
    y /= g;
    if(!np[x] && !np[y]) {
      cout << x << " " << y << nl;
    } else if(x == 1 && y == 1) {
      cout << 2 << " " << 2 << nl;
    } else {
      cout << "impossible" << nl;
    }
  }

  return 0;
}
