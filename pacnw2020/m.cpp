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

  int n, m;
  cin >> n >> m;
  vector<int> v(n);
  for(int i=0; i<n; i++) {
    cin >> v[i];
  }
  sort(v.begin(), v.end());
  vector<int> pref(n+1);
  partial_sum(v.begin(), v.end(), pref.begin() + 1);

  int ans = m;
  if(pref[n] <= m) {
    ans = min(ans, pref[n]);
  }
  vector<bool> have(m+1);
  have[0] = true;
  for(int i=n-1; i>=0; i--) {
    for(int j=m; j>=v[i]; j--) {
      have[j] = have[j] | have[j-v[i]];
    }
    if(pref[i] <= m) {
      for(int j=m-pref[i]; j>=0; j--) {
        if(have[j] && m-pref[i]-j < v[i]) {
          ans = min(ans, pref[i] + j);
        }
      }
    }
  }
  cout << ans << nl;

  return 0;
}
