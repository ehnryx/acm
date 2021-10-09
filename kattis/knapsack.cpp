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

const int N = 2e3+1;
int dp[N][N], pre[N][N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  ld cap; int n;
  while (cin >> cap >> n) {
    int c = llround(floor(cap));
    memset(dp, -1, sizeof dp);
    dp[0][0] = 0;

    int value, weight;
    for (int i=1; i<=n; i++) {
      cin >> value >> weight;
      for (int j=0; j<=c; j++) {
        if (dp[i-1][j] != -1 && dp[i-1][j] > dp[i][j]) {
          dp[i][j] = dp[i-1][j];
          pre[i][j] = j;
        }
        if (j>=weight && dp[i-1][j-weight] != -1 && dp[i-1][j-weight]+value > dp[i][j]) {
          dp[i][j] = dp[i-1][j-weight]+value;
          pre[i][j] = j-weight;
        }
      }
    }

    int best = 0;
    for (int w=1; w<=c; w++) {
      if (dp[n][w] > dp[n][best]) {
        best = w;
      }
    }

    vector<int> ans;
    for (int i=n; i>0; i--) {
      int nxt = pre[i][best];
      if (nxt != best) ans.push_back(i-1);
      best = nxt;
    }
    cout << ans.size() << nl;
    for (int it : ans) {
      cout << it << " ";
    }
    cout << nl;
  }

  return 0;
}
