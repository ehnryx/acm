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
  for(int testnum=1; testnum<=T; testnum++) {
    cout << "Case " << testnum << ": ";

    static const int L = 17;
    int n, w, m;
    cin >> n >> w >> m;
    if(w == 1) m = 1;

    vector<int> a(n+1);
    vector rmq(n+1, vector<int>(L));
    for(int i=1; i<=n; i++) {
      cin >> a[i];
      rmq[i][0] = a[i];
    }
    for(int j=1; j<L; j++) {
      for(int i=1; i+(1<<j)-1<=n; i++) {
        rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
      }
    }
    function<int(int,int)> query = [=](int l, int r) {
      assert(l <= r);
      int j = 31 - __builtin_clz(r-l+1);
      return min(rmq[l][j], rmq[r-(1<<j)+1][j]);
    };

    vector<ll> dp(n+1), ndp(n+1);
    for(int i=2; i<=n; i++) {
      dp[i] = a[i] - query(1, i-1);
    }

    function<void(int,int,int,int)> solve = [&](int l, int r, int s, int e) {
      if(l > r) return;
      int j = (l+r) / 2;
      int best = -1;
      for(int k=min(e,j-2); k>=max(s,j-w); k--) {
        ll cur = dp[k] + a[j] - query(k+1, j-1);
        if(cur > ndp[j]) {
          ndp[j] = cur;
          best = k;
        }
      }
      if(best == -1) {
        solve(j+1, r, s, e);
      } else {
        solve(l, j-1, s, best);
        solve(j+1, r, best, e);
      }
    };

    ll ans = *max_element(dp.begin(), dp.end());
    for(int j=1; j<m; j++) {
      fill(ndp.begin(), ndp.end(), -INFLL);
      solve(1, n, 1, n);
      swap(dp, ndp);
      ans = max(ans, *max_element(dp.begin(), dp.end()));
    }
    cout << ans << nl;
  }

  return 0;
}
