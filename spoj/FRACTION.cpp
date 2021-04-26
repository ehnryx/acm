#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../lca/numbers/fraction.h"

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

using F = fraction<ll>;
void generate(vector<F>& all, int n, const F& left, const F& right) {
  if (left.den + right.den > n) return;
  F mediant(pair(left.num + right.num, left.den + right.den));
  generate(all, n, left, mediant);
  all.push_back(mediant);
  generate(all, n, mediant, right);
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

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    vector<F> all;
    all.emplace_back(pair(0, 1));
    generate(all, n, 0, 1);
    all.emplace_back(pair(1, 1));
    for(int i=0; i<m; i++) {
      int v;
      cin >> v;
      cout << all[v - 1] << nl;
    }
  }

  return 0;
}
