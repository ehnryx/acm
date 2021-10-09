#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

int h[11][11][11];
int dp[11][11][11];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  freopen("commandos.in", "r", stdin);

  int T;
  cin >> T;
  while (T--) {
    memset(dp, 0, sizeof dp);
    memset(h, 0, sizeof h);
    int n;
    cin >> n;

    int x, y, z, t;
    for (int i = 0; i < n; i++) {
      cin >> x >> y >> z >> t;
      h[x][y][z] = t;
    }
    for (int i = 10; i > 0; i--) {
      for (int j = 1; j <= 10; j++) {
        for (int k = 1; k <= 10; k++) {
          if  (i < 10 && dp[i+1][j][k] > dp[i][j][k])
            dp[i][j][k] = dp[i+1][j][k];
          if (j > 1 && dp[i][j-1][k] > dp[i][j][k])
            dp[i][j][k] = dp[i][j-1][k];
          if (k > 1 && dp[i][j][k-1] > dp[i][j][k])
            dp[i][j][k] = dp[i][j][k-1];
          dp[i][j][k] += h[i][j][k];
        }
      }
    }
    cout << dp[1][10][10] << nl;
  }

  return 0;
}
