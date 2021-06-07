#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#ifdef HENRYX
#include "../../lca/graph/push_relabel.h"
#else
#include "push_relabel.h"
#endif

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

  int n, x, y;
  cin >> n >> x >> y;
  vector<ll> a(n), b(n);
  for(int i=0; i<n; i++) {
    cin >> a[i] >> b[i];
  }

  int source = 2*n;
  int sink = 2*n + 1;
  push_relabel<int> graph(2*n + 2);
  static const int M = 1e6;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(a[i]*x <= a[j]*M && a[j]*M <= a[i]*y
          && b[i]*x <= b[j]*M && b[j]*M <= b[i]*y) {
        graph.add_edge(i, n + j, 1);
      }
    }
    graph.add_edge(source, i, 1);
    graph.add_edge(n + i, sink, 1);
  }
  cout << n - graph.flow(source, sink) << nl;

  return 0;
}
