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

const int N = 1e4+1;

int cost[4][7][7][13];
int dp[N][7];

const vector<int> black = {
  0xDEAD, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0
};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  assert(black.size() > 88);
  memset(cost, INF, sizeof cost);
  memset(dp, INF, sizeof dp);

  for (int t=0; t<4; t++) {
    for (int i=1; i<=5; i++) {
      cost[t][i][i][0] = 0;
    }
  }

  int v[4], n; // ww wb bw bb
  for (int i=0; i<4; i++) {
    cin >> v[i];
  }
  cin >> n;

  int fl, fu, a, b, c;
  for (int r=0; r<4; r++) {
    while (v[r]--) {
      cin >> fl >> fu;
      for (int i=1; i<=12; i++) {
        cin >> a;
        cost[r][fl][fu][i] = min(cost[r][fl][fu][i], a);
      }
    }
  }

  int p;
  cin >> p;
  for (int i=1; i<=5; i++) {
    dp[1][i] = 0;
  }

  for (int i=2; i<=n; i++) {
    cin >> c;
    a = min(p,c);
    b = max(p,c);

    int len = abs(a-b);
    int t = 0;
    if (black[a] && black[b]) t = 3;
    else if (black[a]) t = 2;
    else if (black[b]) t = 1;

    if (p < c) {
      for (int j=1; j<=5; j++) {
        for (int k=1; k<=5; k++) {
          dp[i][k] = min(dp[i][k], dp[i-1][j] + cost[t][j][k][len]);
        }
      }
    } else {
      for (int j=1; j<=5; j++) {
        for (int k=1; k<=5; k++) {
          dp[i][j] = min(dp[i][j], dp[i-1][k] + cost[t][j][k][len]);
        }
      }
    }
    p = c;
  }

  int ans = INF;
  for (int i=1; i<=5; i++) {
    ans = min(ans, dp[n][i]);
  }
  cout << ans << nl;

  return 0;
}
