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
  vector<ll> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  partial_sum(begin(a), end(a), begin(a));
  vector<int> have(n, -1);
  for(int i=0; i<=n; i++) {
    int r = a[i] % n;
    if (have[r] != -1) {
      cout << i - have[r] << nl;
      for (int j = have[r] + 1; j <= i; j++) {
        cout << j << " ";
      }
      cout << nl;
      return 0;
    }
    have[r] = i;
  }
  assert(false);

  return 0;
}
