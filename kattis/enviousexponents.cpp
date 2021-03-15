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

  ll n;
  int k;
  cin >> n >> k;
  n++;
  while(__builtin_popcountll(n) > k) {
    bool ones = false;
    for(int i=0; ; i++) {
      if(n & 1LL<<i) {
        n ^= 1LL<<i;
        ones = true;
      } else if(ones) {
        n ^= 1LL<<i;
        break;
      }
    }
  }
  while(__builtin_popcountll(n) < k) {
    for(int i=0; ; i++) {
      if(!(n & 1LL<<i)) {
        n ^= 1LL<<i;
        break;
      }
    }
  }
  cout << n << nl;

  return 0;
}
