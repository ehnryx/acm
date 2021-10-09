#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 50+1;
const int T = 1e3+1;
ll dp[N][T];
int pre[N][T];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  for (int t, n; cin >> t >> n; ) {
    memset(dp[0], 0, sizeof dp[0]);
    dp[0][0] = 1;
    for (int i=1; i<=n; i++) {
      int x;
      cin >> x;
      for (int j=0; j<=t; j++) {
        dp[i][j] = dp[i-1][j];
        pre[i][j] = j;
        if (j-x>=0 && dp[i-1][j-x]) {
          ll cur = dp[i-1][j-x] + (1LL<<(N-i));
          if (cur > dp[i][j]) {
            dp[i][j] = cur;
            pre[i][j] = j-x;
          }
        }
      }
    }

    int cur = 0;
    for (int i=0; i<=t; i++) {
      if (dp[n][i]) cur = i;
    }
    vector<int> ans;
    ans.push_back(cur);
    for (int i=n; i>=1; i--) {
      if (cur != pre[i][cur]) {
        ans.push_back(cur - pre[i][cur]);
      }
      cur = pre[i][cur];
    }
    reverse(ans.begin(), ans.end());
    for (int i=0; i<ans.size(); i++) {
      if (i>0) cout << " ";
      cout << ans[i];
    }
    cout << nl;
  }

  return 0;
}
