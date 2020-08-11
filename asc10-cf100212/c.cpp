//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "codes"

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

const int N = 2e3 + 1;
ll a[N];
ll dp[N][N];
int opt[N][N];
string ans[N];

void recover(int l, int r) {
  if(l == r) return;
  for(int i=l; i<=r; i++) {
    ans[i].push_back(i <= opt[l][r] ? '0' : '1');
  }
  recover(l, opt[l][r]);
  recover(opt[l][r] + 1, r);
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  memset(dp, INF, sizeof dp);

  int n;
  cin >> n;
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    dp[i][i] = 0;
    opt[i][i] = i;
  }
  partial_sum(a, a+n+1, a);

  for(int len=2; len<=n; len++) {
    for(int i=1; i+len-1<=n; i++) {
      int j = i + len - 1;
      int l = max(opt[i][j-1], i);
      int r = min(opt[i+1][j], j-1);
      for(int k=l; k<=r; k++) {
        ll cur = dp[i][k] + dp[k+1][j] + a[j] - a[i-1];
        if(cur < dp[i][j]) {
          dp[i][j] = cur;
          opt[i][j] = k;
        }
      }
    }
  }

  cerr << "length: " << dp[1][n] << nl;
  recover(1, n);
  for(int i=1; i<=n; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
