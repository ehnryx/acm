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
  vector<ld> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  sort(begin(a), end(a));
  ld sum = accumulate(begin(a), end(a), (ld)0);

  ld ans = 0;
  for(int i=0; !empty(a); i^=1) {
    if(i == 0) {
      ans += a.back();
      a.pop_back();
    } else {
      vector<ld> b(size(a)-1);
      for(int j=1; j<size(a); j++) {
        b[j-1] = (j * a[j] + (size(a)-j) * a[j-1]) / size(a);
      }
      a = move(b);
    }
  }
  cout << ans << " " << sum - ans << nl;

  return 0;
}
