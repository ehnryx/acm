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

const int N = 3e5+1;
const int M = 11;
int dp[N][M];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;

  dp[0][m] = 0;
  for (int j = 0; j < m; j++) {
    dp[0][j] = -INF;
  }

  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;

    for (int j = 0; j <= m; j++) {
      dp[i][j] = -INF;
    }

    // do nothing
    dp[i][0] = max(dp[i][0], dp[i-1][0]);
    for (int j = 0; j < m; j++) {
      dp[i][j] = max(dp[i][j], dp[i-1][j+1]);
    }

    // use
    dp[i][m-1] = max(dp[i][m-1], dp[i-1][0] + a);
  }

  int ans = 0;
  for (int j = 0; j <= m; j++) {
    ans = max(ans, dp[n][j]);
  }
  cout << ans << nl;

  return 0;
}
