//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 52;
int dp[N][N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    string s, t;
    cin >> s >> t;
    for(char& c : s) {
      if(c == 'T') c = '9'+1;
      else if(c == 'J') c = '9'+2;
      else if(c == 'Q') c = '9'+3;
      else if(c == 'K') c = '9'+4;
      else if(c == 'A') c = '9'+5;
    }
    for(char& c : t) {
      if(c == 'T') c = '9'+1;
      else if(c == 'J') c = '9'+2;
      else if(c == 'Q') c = '9'+3;
      else if(c == 'K') c = '9'+4;
      else if(c == 'A') c = '9'+5;
    }
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    int n = s.size();
    memset(dp, 0, sizeof dp);
    for(int i=0; i<=n; i++) {
      for(int j=0; j<=n; j++) {
        if(i>0) dp[i][j] = max(dp[i][j], dp[i-1][j]);
        if(j>0) dp[i][j] = max(dp[i][j], dp[i][j-1]);
        if(i>0 && j>0) {
          if(s[i-1] < t[j-1]) dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 2);
          if(s[i-1] == t[j-1]) dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
        }
      }
    }
    cout << dp[n][n] << nl;
  }

  return 0;
}
