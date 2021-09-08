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

  int n, m;
  cin >> n >> m;
  vector<int> a(n+m + 1);
  for(int i=1; i<=n+m; i++) {
    cin >> a[i];
  }

  vector<bool> vis(n+m + 1);
  int ans = 0;
  vector<int> left, right;
  for(int i=1; i<=n+m; i++) {
    if(vis[i]) continue;
    vis[i] = true;
    int length = 1;
    int minv = i;
    int maxv = i;
    for(int u=a[i]; u!=i; u=a[u]) {
      vis[u] = true;
      length += 1;
      maxv = max(maxv, u);
      minv = min(minv, u);
    }
    if (length == 1) continue;
    if (maxv <= n) {
      left.push_back(length);
    } else if (minv > n) {
      right.push_back(length);
    } else {
      ans += length - 1;
    }
  }

  while(!empty(left) && !empty(right)) {
    ans += left.back() + right.back();
    left.pop_back();
    right.pop_back();
  }
  while(!empty(left)) {
    ans += left.back() + 1;
    left.pop_back();
  }
  while(!empty(right)) {
    ans += right.back() + 1;
    right.pop_back();
  }

  cout << ans << nl;

  return 0;
}
