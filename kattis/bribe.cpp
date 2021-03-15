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

  int T;
  cin >> T;
  while(T--) {
    int n, c, m;
    cin >> n >> c >> m;
    vector<int> bribe(n), prob(n);
    for(int i=0; i<n; i++) {
      cin >> bribe[i] >> prob[i];
    }

    vector dp(1<<n, vector<ld>(c+1, -2));
    function<ld(int,int,int)> solve = [&](int bm, int need, int money) {
      if(dp[bm][need] > -1) return dp[bm][need];
      if(need == 0) return dp[bm][need] = 1;
      if(need > __builtin_popcount(bm)) return dp[bm][need] = 0;
      ld res = 0;
      for(int i=0; i<n; i++) {
        if(!(bm & 1<<i) || bribe[i] > money) continue;
        ld p = (ld)prob[i] / 100;
        ld success = p * solve(bm ^ 1<<i, need - 1, money - bribe[i]);
        ld failure = (1-p) * solve(bm ^ 1<<i, need, money - bribe[i]);
        res = max(res, success + failure);
      }
      return dp[bm][need] = res;
    };

    cout << solve((1<<n)-1, c, m) << nl;
  }

  return 0;
}
