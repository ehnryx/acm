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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



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
  vector<int> a(1<<n), sum((1<<n) + 1);
  for(int i=0; i<1<<n; i++) {
    int id = 0;
    for(int j=0; j<n; j++) {
      id |= ((i >> j) & 1) << (n-1-j);
    }
    cin >> a[id];
  }
  partial_sum(a.begin(), a.end(), sum.begin() + 1);

  int ans = 2*(1<<n) - 1;
  for(int len=2; len<=1<<n; len*=2) {
    for(int i=0; i<1<<n; i+=len) {
      if(sum[i+len] - sum[i] == 0 || sum[i+len] - sum[i] == len) {
        ans -= 2;
      }
    }
  }
  cout << ans << nl;

  return 0;
}
