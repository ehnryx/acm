#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

bool isvowel(char c) {
  return c=='A'||c=='E'||c=='I'||c=='O'||c=='U';
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string s;
  cin>>s;
  int n = s.size();

  ll dp[n][1<<3][2];
  memset(dp,0,sizeof dp);
  for(int i=0;i<n;i++) {
    if(i==0) {
      if(isvowel(s[i])) dp[i][0b001][0] = 1;
      else if(s[i]=='L') dp[i][0b000][1] = 1;
      else if(s[i]!='_') dp[i][0b000][0] = 1;
      else {
        dp[i][0b001][0] = 5;
        dp[i][0b000][1] = 1;
        dp[i][0b000][0] = 20;
      }
    } else {
      for(int j=0;j<1<<3;j++) {
        if(i>=2 && j%0b111==0) continue;
        // no L
        if(isvowel(s[i])) {
          if(j&1) {
            dp[i][j][0] += dp[i-1][j>>1|0b100][0];
            dp[i][j][0] += dp[i-1][j>>1|0b000][0];
            dp[i][j][1] += dp[i-1][j>>1|0b100][1];
            dp[i][j][1] += dp[i-1][j>>1|0b000][1];
          }
        } else if(s[i]=='L') {
          if(!(j&1)) {
            dp[i][j][1] += dp[i-1][j>>1|0b100][0];
            dp[i][j][1] += dp[i-1][j>>1|0b000][0];
            dp[i][j][1] += dp[i-1][j>>1|0b100][1];
            dp[i][j][1] += dp[i-1][j>>1|0b000][1];
          }
        } else if(s[i]!='_') {
          if(!(j&1)) {
            dp[i][j][0] += dp[i-1][j>>1|0b100][0];
            dp[i][j][0] += dp[i-1][j>>1|0b000][0];
            dp[i][j][1] += dp[i-1][j>>1|0b100][1];
            dp[i][j][1] += dp[i-1][j>>1|0b000][1];
          }
        } else {
          if(j&1) {
            dp[i][j][0] += dp[i-1][j>>1|0b100][0] * 5;
            dp[i][j][0] += dp[i-1][j>>1|0b000][0] * 5;
            dp[i][j][1] += dp[i-1][j>>1|0b100][1] * 5;
            dp[i][j][1] += dp[i-1][j>>1|0b000][1] * 5;
          } else {
            dp[i][j][1] += dp[i-1][j>>1|0b100][0];
            dp[i][j][1] += dp[i-1][j>>1|0b000][0];
            dp[i][j][1] += dp[i-1][j>>1|0b100][1];
            dp[i][j][1] += dp[i-1][j>>1|0b000][1];
            dp[i][j][0] += dp[i-1][j>>1|0b100][0] * 20;
            dp[i][j][0] += dp[i-1][j>>1|0b000][0] * 20;
            dp[i][j][1] += dp[i-1][j>>1|0b100][1] * 20;
            dp[i][j][1] += dp[i-1][j>>1|0b000][1] * 20;
          }
        }
      }
    }
  }

  ll ans = 0;
  for(int bm=0;bm<1<<3;bm++) {
    ans += dp[n-1][bm][1];
  }
  cout<<ans<<nl;

  return 0;
}
