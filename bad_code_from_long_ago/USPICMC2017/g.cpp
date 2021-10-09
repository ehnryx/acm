#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int len;
  cin >> len;
  int cost[26][26];
  for (int i = 0; i < 26; i++) 
    for (int j = 0; j < 26; j++) 
      cin >> cost[i][j];
  int dp[len+1][26];
  memset(dp, INF, sizeof(dp));
  memset(dp[1], 0, sizeof(dp[1]));
  for (int i = 2; i <= len; i++) {
    for (int next = 0; next < 26; next++) {
      for (int prev = 0; prev < 26; prev++) {
        dp[i][next] = min(dp[i][next], dp[i-1][prev] + cost[prev][next]);
      }
    }
  }
  int ans = INF;
  for (int i = 0; i < 26; i++) {
    ans = min(ans, dp[len][i]);
  }
  cout << ans << nl;

  return 0;
}
