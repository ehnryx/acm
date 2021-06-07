#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/data_structure/segment_tree.h"

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

struct Node {
  ll value, lazy; int length;
  Node(): value(0), lazy(0), length(1) {}
  ll get() const { return value; }
  ll put(ll v) { value += v * length; lazy += v; }
  void push(Node& a, Node& b) {
    if(lazy) { a.put(lazy); b.put(lazy); lazy = 0; }
  }
  void pull(const Node& a, const Node& b) {
    value = a.value + b.value;
    length = a.length + b.length;
  }
  static ll default_value() { assert(false); }
  static ll merge(ll a, ll b) { return a + b; }
};

ll nc2(int n) {
  return (ll)n * (n-1) / 2;
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
    int n;
    cin >> n;
    segment_tree<Node, ll> st(n, true);
    vector<int> a(n);
    map<int,int> cnt;
    for(int i=0; i<n; i++) {
      cin >> a[i];
      cnt[a[i]] += 1;
      st.update(i, n-1, nc2(cnt[a[i]]) - nc2(cnt[a[i]] - 1));
    }
    for(int i=0; i<n; i++) {
    }
  }

  return 0;
}
