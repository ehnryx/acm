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

  const int M = 1e5 + 1;
  vector<int> ans(M);
  for(int i=4; i<M; i++) {
    bool is_prime = true;
    ans[i] = -1;
    for(int j=2; j*j<=i; j++) {
      if(i % j == 0) {
        is_prime = false;
        if(ans[j] == -1) ans[i] = max(ans[i], j);
        if(ans[i/j] == -1) ans[i] = max(ans[i], i/j);
      }
    }
    if(is_prime) ans[i] = 0;
  }

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    cout << ans[n] << nl;
  }

  return 0;
}
