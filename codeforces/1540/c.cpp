#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/number/mod_int.h"
#include "../../../lca/data_structure/fenwick_tree.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

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
  vector<int> c(n+1), b(n+1);
  for(int i=1; i<=n; i++) {
    cin >> c[i];
  }
  for(int i=1; i<=n-1; i++) {
    cin >> b[i];
  }

  vector<int> sum(n+1);
  partial_sum(begin(c), end(c), begin(sum));

  vector<int> prefix(n+1);
  for(int k=1; k<=n; k++) {
    for(int j=1; j<k; j++) {
      prefix[k] += b[j] * (k - j);
    }
  }

  int m;
  cin >> m;
  vector<pair<int,int>> queries;
  for(int i=0; i<m; i++) {
    int x;
    cin >> x;
    queries.emplace_back(x, i);
  }
  sort(begin(queries), end(queries), greater<>());

  vector<Int> ans(m);
  map<int, Int> memo;
  for(auto [x, qid] : queries) {
    if (memo.count(x)) {
      ans[qid] = memo[x];
      continue;
    }
    if(n*x + prefix[n] > sum[n]) {
      ans[qid] = 0;
    } else if(n*x + prefix[n] <= 0) {
      ans[qid] = 1;
      for(int i=1; i<=n; i++) {
        ans[qid] *= c[i] + 1;
      }
    } else {
      vector dp(n+1, fenwick_tree<Int>(sum.back() + 1));
      dp[0].update(0, 1);
      for(int i = 1; i <= n; i++) {
        int start = max(0, i*x + prefix[i]);
        for(int s = start; s <= sum[i]; s++) {
          dp[i].update(s, dp[i-1].query_range(s - min(c[i], s), s));
        }
      }
      ans[qid] = dp[n].query_range(n*x + prefix[n], sum[n]);
    }
    memo[x] = ans[qid];
  }

  for(int i=0; i<m; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
