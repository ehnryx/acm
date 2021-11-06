#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"
#include "../../lca/tree/range_query_tree.h"

//#define FILENAME sadcactus

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct node {
  ll sum = 0;
  ll get() const { return sum; }
  void put(int v) { sum += v; }
  void pull(const node& a, const node& b) { sum = a.sum + b.sum; }
  static ll merge(ll a, ll b) { return a + b; }
};

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

  int n, m;
  cin >> n >> m;
  vector<int> val(n);
  for(int i=0; i<n; i++) {
    cin >> val[i];
  }
  vector<vector<int>> adj(n);
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  range_query_tree<segment_tree<node, ll>, ll> st(adj, 0);
  for(int i=0; i<n; i++) {
    st.update_point(i, val[i]);
  }

  while(m--) {
    int t;
    cin >> t;
    if(t == 0) {
      int i, x;
      cin >> i >> x;
      st.update_point(i, x);
    } else {
      int a, b;
      cin >> a >> b;
      cout << st.query_path(a, b, true, 0, node::merge) << nl;
    }
  }

  return 0;
}
