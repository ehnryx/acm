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

  ll ans[201];
  memset(ans, 0, sizeof(ans));
  map<ll,ll> dp[201];
  dp[0].insert(pair<ll,ll>(0,1));
  for (int i = 0; i < 200; i++) {
    for (pair<ll,ll> curr: dp[i]) {
      dp[i+1][curr.first+curr.second] = max(dp[i+1][curr.first+curr.second], curr.second);
      if (i != 0) dp[i+1][curr.first] = max(dp[i+1][curr.first], curr.first);
      ans[i+1] = max(ans[i+1], curr.first+curr.second);
    }
  }

  ll a;
  int T;
  cin >> T;
  for (int cc = 0; cc < T; cc++) {
    cin >> a;
    for (int i = 0; i < 200; i++) {
      if (a <= ans[i]) {
        cout << i << nl;
        break;
      }
    }
  }

  return 0;
}
