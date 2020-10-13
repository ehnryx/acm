//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve_case() {
  int n;
  cin >> n;
  vector<int> a(n+1), sum(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    sum[i] = sum[i-1] + a[i];
  }
  if(n == 1) {
    cout << "r" << nl;
    return;
  }
  if(__builtin_popcount(sum[n]) != 1) {
    cout << "no" << nl;
    return;
  }

  vector dp(n + 1, vector<pair<int,int>>(sum[n] + 1, make_pair(-1, 0)));
  dp[0][0] = make_pair(0, 0);
  for(int i=1; i<=n; i++) {
    for(int j=0; j<=sum[i]; j++) {
      // place right
      if(dp[i-1][j].first != -1) {
        int left = j;
        int right = sum[i-1] - left;
        if(__builtin_ctz(a[i]) <= __builtin_ctz(right | 1<<30)) {
          if(left && __builtin_clz(left) == __builtin_clz(right + a[i])) {
            int msb = 1 << (31 - __builtin_clz(left));
            dp[i][left + msb] = make_pair(j, 'r');
          } else {
            dp[i][j] = make_pair(j, 'r');
          }
        }
      }
      // place left
      if(j >= a[i] && dp[i-1][j-a[i]].first != -1) {
        int left = j-a[i];
        int right = sum[i-1] - left;
        if(__builtin_ctz(a[i]) <= __builtin_ctz(left | 1<<30)) {
          if(right && __builtin_clz(left + a[i]) == __builtin_clz(right)) {
            int msb = 1 << (31 - __builtin_clz(right));
            dp[i][left + a[i] + msb] = make_pair(j-a[i], 'l');
          } else {
            dp[i][j] = make_pair(j-a[i], 'l');
          }
        }
      }
    }

    for(int j=0; j<=sum[i]; j++) {
      if(dp[i][j].first != -1) continue;
      int left = j;
      int right = sum[i] - j;
      if(__builtin_clz(left << 1 | 1) < __builtin_clz(right << 1 | 1)) {
        int msb = 1 << (31 - __builtin_clz(left));
        dp[i][j] = dp[i][j-msb];
      } else if(__builtin_clz(left << 1 | 1) > __builtin_clz(right << 1 | 1)) {
        int msb = 1 << (31 - __builtin_clz(right));
        dp[i][j] = dp[i][j+msb];
      }
    }
  }

  if(dp[n][sum[n]].first == -1) {
    cout << "no" << nl;
    return;
  }

  string ans;
  for(int i=n, j=sum[n]; i>0; j=dp[i--][j].first) {
    ans.push_back(dp[i][j].second);
  }
  reverse(ans.begin(), ans.end());
  cout << ans << nl;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  while(T--) {
    solve_case();
  }

  return 0;
}
