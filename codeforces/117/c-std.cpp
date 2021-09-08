#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2")
#ifdef ONLINE_JUDGE
#pragma GCC target("tune=native")
#endif

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());



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

  static const int N = 5000;

  int n;
  cin >> n;
  array<bitset<N>, N> in, out;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    reverse(begin(s), end(s));
    out[i] = bitset<N>(s);
    for(int j=0; j<n; j++) {
      if(out[i][j]) {
        in[j][i] = 1;
      }
    }
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      if(!out[i][j]) continue;
      bitset<N> it = out[j] & in[i];
      if(it.any()) {
        int k = it._Find_first();
        cout << i+1 << " " << j+1 << " " << k+1 << nl;
        return 0;
      }
    }
  }

  cout << -1 << nl;

  return 0;
}
