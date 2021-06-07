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

  vector<int> ans = { 22, 210, 1155 };
  for(int i=1; i<=10000; i++) {
    if(i == 22 || i == 210 || i == 1155) continue;
    bool a = (i % 2 == 0);
    bool b = (i % 3 == 0 || i % 5 == 0 || i % 7 == 0);
    if(a && b) ans.push_back(i);
  }

  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    cout << ans[i] << " ";
  }
  cout << nl;

  return 0;
}
