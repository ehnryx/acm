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



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  string s, t;
  cin >> s >> t;
  int n = s.size();
  int m = t.size();

  int dp[n+1][m+1];
  pii p[n+1][m+1];
  memset(dp, 0, sizeof dp);
  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      if (s[i] == t[j]) {
        dp[i+1][j+1] = dp[i][j] + 1;
        p[i+1][j+1] = pii(i,j);
      } else {
        dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j]);
        if (dp[i+1][j+1] == dp[i][j+1]) {
          p[i+1][j+1] = pii(i,j+1);
        } else {
          p[i+1][j+1] = pii(i+1,j);
        }
      }
    }
  }

  string ans;
  for (int i=n,j=m; i>0 && j>0; tie(i,j)=p[i][j]) {
    if (p[i][j].first != i && p[i][j].second != j) {
      ans.push_back(s[i-1]);
    }
  }
  reverse(ans.begin(), ans.end());
  cout << ans << nl;

  return 0;
}
