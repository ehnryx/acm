#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/tree/lca_binary_jumping.h"

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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<vector<int>> adj(n+1);
    for(int i=1; i<n; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    lca_binary_jumping tree(move(adj), 1);

    int m;
    cin >> m;
    for(int i=0; i<m; i++) {
      int k;
      cin >> k;
      vector<pair<int,int>> order;
      for(int j=0; j<k; j++) {
        int v;
        cin >> v;
        order.emplace_back(tree.in[v], v);
      }
      sort(begin(order), end(order));

      int jumps = 0;
      bool ok = true;
      for(int j=1; j<k && ok; j++) {
        if(!tree.is_ancestor_of(order[j-1].second, order[j].second)) {
          jumps++;
          ok &= (jumps <= 1);
          ok &= tree.is_ancestor_of(
              tree.lca(order[j-1].second, order[j].second),
              order.front().second,
              false); // nonstrict
        }
      }

      if(ok) {
        cout << "yes" << nl;
      } else {
        cout << "no" << nl;
      }
    }
  }

  return 0;
}
