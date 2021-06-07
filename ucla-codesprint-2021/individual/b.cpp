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

  int n;
  cin >> n;
  vector<int> a(n), b(n);
  vector<tuple<int,int,int>> edges;
  for(int i=0; i<n; i++) {
    cin >> a[i] >> b[i];
    for(int j=0; j<i; j++) {
      edges.emplace_back(abs(a[i] - a[j]) + abs(b[i] - b[j]), i, j);
    }
  }
  sort(begin(edges), end(edges));

  vector<int> dsu(n, -1);
  function<int(int)> find = [&](int i) {
    if(dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  };
  auto link = [&](int i, int j) {
    i = find(i); j = find(j);
    if(i == j) return false;
    dsu[i] = j;
    return true;
  };

  int ans = 0;
  for (auto [d, i, j] : edges) {
    if(link(i, j)) {
      ans += d;
    }
  }
  cout << 2 * ans << nl;

  return 0;
}
