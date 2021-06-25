#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/data_structure/union_find.h"
#include "../../../lca/number/mod_int.h"

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
constexpr ll MOD = 1e9 + 7;
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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<int> a(n+1), b(n+1), remap(n+1);
    for(int i=1; i<=n; i++) {
      cin >> a[i];
    }
    for(int i=1; i<=n; i++) {
      cin >> b[i];
      remap[b[i]] = i;
    }

    union_find dsu(n+1);
    for(int i=1; i<=n; i++) {
      int to = a[remap[a[i]]];
      dsu.link(a[i], to);
    }

    mod_int<MOD> ans = 1;
    for(int i=1; i<=n; i++) {
      if(dsu[i] == i) {
        ans *= 2;
      }
    }
    cout << ans << nl;
  }

  return 0;
}
