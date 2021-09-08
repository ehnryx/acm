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

  int n, m, r;
  cin >> n >> m >> r;

  vector<tuple<int, int, int>> card;
  for(int i=0; i<n; i++) {
    int d, k, c;
    cin >> d >> k >> c;
    card.emplace_back(d, k, c);
  }
  vector<int> last(n);

  vector<pair<int,int>> sad;
  for(int i=0; i<m; i++) {
    int p, q;
    cin >> p >> q;
    sad.emplace_back(p, q);
  }
  sort(begin(sad), end(sad));

  vector<int> ts(1, -INF);
  for(auto [p, q] : sad) {
    while(q--) {
      ts.push_back(p);
    }
  }

  int len = size(ts) - 1;
  vector<ll> dp(len + 1, -1);
  dp[0] = 0;
  for(int i=1; i<=len; i++) {
    dp[i] = dp[i-1] + r;
    for(int j=0; j<n; j++) {
      auto [d, k, c] = card[j];
      while(i - last[j] > k || ts[i] - ts[last[j]+1] >= d) {
        last[j]++;
      }
      dp[i] = min(dp[i], dp[last[j]] + c);
    }
  }

  cout << dp[len] << nl;

  return 0;
}
