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

const int N = 400+1;
int cost[N][N], col[N][N];
int dp[N][N], pre[N][N];

int solve(int bm, int n) {
  memset(dp, INF, sizeof dp);
  memset(pre, -1, sizeof pre);
  dp[0][0] = ((bm&1<<col[0][0]) ? cost[0][0] : INF);
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (bm&1<<col[i][j]) {
        if (i>0) {
          int nxt = dp[i-1][j] + cost[i][j];
          if (nxt < dp[i][j]) {
            dp[i][j] = nxt;
            pre[i][j] = 0;
          }
        }
        if (j>0) {
          int nxt = dp[i][j-1] + cost[i][j];
          if (nxt < dp[i][j]) {
            dp[i][j] = nxt;
            pre[i][j] = 1;
          }
        }
      }
    }
  }
  return dp[n-1][n-1];
}

void recover(vector<int>& path, int n) {
  int i, j;
  i = j = n-1;
  path = {n-1,n-1};
  while (pre[i][j] != -1) {
    if (pre[i][j] == 0) i--;
    else j--;
    path.push_back(j);
    path.push_back(i);
  }
  reverse(path.begin(), path.end());
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, k, w;
  cin >> n >> k >> w;
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      cin >> cost[i][j];
    }
  }
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      cin >> col[i][j];
      col[i][j]--;
    }
  }

  int ans = INF;
  vector<int> path;
  for (int bm=1; bm<1<<k; bm++) {
    int cnt = __builtin_popcount(bm);
    if (cnt < ans && solve(bm, n) <= w) {
      ans = cnt;
      recover(path, n);
    }
  }

  if (ans == INF) {
    cout << -1 << nl;
  } else {
    cout << ans << nl;
    for (int it : path) {
      cout << it+1 << " ";
    }
    cout << nl;
  }

  return 0;
}
