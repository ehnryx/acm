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
  vector<int> a(n);
  map<int,int> remap;
  for(int i=0; i<n; i++) {
    cin >> a[i];
    remap[a[i]];
  }
  int rid = 0;
  for(auto& it : remap) {
    it.second = rid++;
  }

  for(int i=0; i<n; i++) {
    a[i] = remap[a[i]];
  }

  vector<int> dp(n, -INF);
  for(int i=0; i<n; i++) {
    dp[a[i]] = 1;
    if(a[i]) dp[a[i]] = max(dp[a[i]], dp[a[i]-1] + 1);
  }
  cout << n - *max_element(begin(dp), end(dp)) << nl;

  return 0;
}
