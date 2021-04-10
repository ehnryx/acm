#pragma GCC optimize("O3")
//#pragma GCC target("avx2,sse4,fma")

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

  for(int n, m; cin >> n >> m && n; ) {
    unordered_map<string,int> remap;
    vector<pair<int,int>> edges;
    for(int i=0, rid=0; i<m; i++) {
      string a, b;
      cin >> a >> b;
      if(!remap.count(a)) remap[a] = rid++;
      if(!remap.count(b)) remap[b] = rid++;
      edges.emplace_back(remap[a], remap[b]);
    }
    n = size(remap);

    vector<bool> bad(1<<n);
    for(int bm=0; bm<1<<n; bm++) {
      for(auto [a, b] : edges) {
        if((bm & 1<<a) && (bm & 1<<b)) {
          bad[bm] = true;
          break;
        }
      }
    }

    int all = (1<<n) - 1;
    vector<int> dp(1<<n, n);
    dp[0] = 0;
    for(int bm=0; bm<1<<n; bm++) {
      if(bad[bm]) continue;
      dp[bm] = 1;
      int other = all & ~bm;
      for(int sm=other; sm; sm=(sm-1)&other) {
        dp[bm | sm] = min(dp[bm | sm], dp[sm] + 1);
      }
    }
    cout << max(1, dp[(1<<n) - 1]) << nl;
  }

  return 0;
}
