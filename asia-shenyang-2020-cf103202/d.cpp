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
  int a = (n+1)/2;
  int b = (n+2)/2;
  cout << (ll)a*b << nl;

  int printed = 0;
  int even = 1;
  int odd = 0;
  int sum = 0;
  string s(n, 0);
  function<bool(int)> solve = [&](int i) {
    if(not (min(even, odd) <= a && max(even, odd) <= b)) {
      return false;
    }

    if(i == n) {
      cout << s << nl;
      return ++printed == 100;
    }

    // try to push b
    (sum ? odd : even) += 1;
    s[i] = 'b';
    if(solve(i+1)) return true;
    (sum ? odd : even) -= 1;

    // try to push r
    sum ^= 1;
    (sum ? odd : even) += 1;
    s[i] = 'r';
    if(solve(i+1)) return true;
    (sum ? odd : even) -= 1;
    sum ^= 1;

    return false;
  };
  solve(0);

  return 0;
}
