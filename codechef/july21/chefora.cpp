#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/number/mod_int.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;
using Ent = mod_int<MOD - 1>;

ll get_pal(int v) {
  ll res = v;
  for (v /= 10; v > 0; v /= 10) {
    res = res * 10 + v % 10;
  }
  return res;
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

  const int N = 1e5 + 1;
  vector<Ent> esum(N);
  for (int i = 1; i < N; i++) {
    esum[i] = esum[i-1] + get_pal(i);
  }

  int T;
  cin >> T;
  while(T--) {
    int l, r;
    cin >> l >> r;
    cout << Int(get_pal(l)).pow((esum[r] - esum[l]).value()) << nl;
  }

  return 0;
}
