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

  int n;
  cin >> n;
  vector<int> a(n), b(n), c(n);
  for(int i=0; i<n; i++) { cin >> a[i]; }
  for(int i=0; i<n; i++) { cin >> b[i]; }
  for(int i=0; i<n; i++) { cin >> c[i]; }
  sort(begin(a), end(a));
  sort(begin(b), end(b));
  sort(begin(c), end(c));

  function<bool(int)> solve = [=](int m) {
    int s = n - m;
    int need = m;
    for(int i=0, j=0; i<n && need; i++) {
      if(a[j] < b[i] && b[i] < c[s+j]) {
        need--;
        j++;
      }
    }
    return need == 0;
  };

  int l = 0;
  int r = n;
  while (l < r) {
    int m = (l + r + 1) / 2;
    if (solve(m)) {
      l = m;
    } else {
      r = m-1;
    }
  }

  cout << r << nl;

  return 0;
}
