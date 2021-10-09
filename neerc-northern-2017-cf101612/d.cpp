#include <bits/stdc++.h>
using namespace std;

#define FILENAME "dividing"

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int INF = 0x3f3f3f3f;

const int N = 4<<20;
int dp[N+1];
int fac[N+1];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  if(fopen(FILENAME ".in", "r")) {
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
  }

  memset(dp, INF, sizeof dp);
  dp[1] = 0;
  dp[2] = 1;
  for(int i=2; i<=N; i++) {
    for(int j=i+i; j<=N; j++) {
      int o = j/i;
      if(dp[i] + dp[o] < dp[j]) {
        dp[j] = dp[i] + dp[o];
        fac[j] = i;
      }
    }
  }

  int T;
  cin >> T;
  while(T--) {
    int n = 0;
    for(int i=0; i<4; i++) {
      int d;
      cin >> d;
      n += 1<<d;
    }
    cout << solve(n) << nl;
    recover(n);
  }

  return 0;
}
