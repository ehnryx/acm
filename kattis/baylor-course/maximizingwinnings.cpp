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

const int N = 50;
const int M = 5e3+1;
int adj[N][N];
int dp1[M][N], dp2[M][N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  for (int n;;) {
    cin >> n;
    if (!n) break;

    for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++) {
        cin >> adj[i][j];
      }
    }

    int m;
    cin >> m;
    fill(&dp1[0][0], &dp1[0][0]+M*N, -INF);
    fill(&dp2[0][0], &dp2[0][0]+M*N, INF);
    dp1[0][0] = dp2[0][0] = 0;
    for (int i=1; i<=m; i++) {
      for (int j=0; j<n; j++) {
        for (int k=0; k<n; k++) {
          dp1[i][j] = max(dp1[i][j], dp1[i-1][k] + adj[k][j]);
          dp2[i][j] = min(dp2[i][j], dp2[i-1][k] + adj[k][j]);
        }
      }
    }

    int maxv = 0;
    int minv = INF;
    for (int j=0; j<n; j++) {
      maxv = max(maxv, dp1[m][j]);
      minv = min(minv, dp2[m][j]);
    }
    cout << maxv << " " << minv << nl;
  }

  return 0;
}
