#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

enum vacation {
  rest,
  gym,
  contest
};

const int N = 100+1;
int dp[N][3];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n;
  cin >> n;

  int a;
  dp[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a;
    dp[i][rest] = 1 + min(dp[i-1][rest], min(dp[i-1][gym], dp[i-1][contest]));
    switch (a) {
      case 0: 
        dp[i][gym] = INF;
        dp[i][contest] = INF;
        break;
      case 1:
        dp[i][gym] = INF;
        dp[i][contest] = min(dp[i-1][rest], dp[i-1][gym]);
        break;
      case 2:
        dp[i][gym] = min(dp[i-1][rest], dp[i-1][contest]);
        dp[i][contest] = INF;
        break;
      case 3:
        dp[i][gym] = min(dp[i-1][rest], dp[i-1][contest]);
        dp[i][contest] = min(dp[i-1][rest], dp[i-1][gym]);
        break;
    }
  }

  int ans = INF;
  for (int i = 0; i < 3; i++) {
    ans = min(ans, dp[n][i]);
  }
  cout << ans << nl;

  return 0;
}
