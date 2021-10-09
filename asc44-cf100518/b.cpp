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
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAGIC = 10;

const int N = 5e3+1;
int a[N], b[N], c[N], d[N];
ld dp[N][N];
int ropt[N][N], lopt[N][N];

ld value(int l, int r) {
  int A = a[r]-a[l];
  int B = b[r]-b[l];
  int C = c[r]-c[l];
  int D = d[r]-d[l];
  if (A == 0) return min(B, C+D);
  if (C == 0) return min(D, A+B);
  ld x = (ld)(C+D-B)/(A+C);
  return A*x + B;
}

ld get(int i, int j, int k) {
  if (i==j) return value(j,k);
  if (j==k) return value(i,j);
  return dp[i][j] + dp[j][k];
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

  int n;
  cin >> n;

  for (int i=1; i<=n; i++) {
    cin >> a[i] >> b[i] >> c[i] >> d[i];
    a[i] += a[i-1];
    b[i] += b[i-1];
    c[i] += c[i-1];
    d[i] += d[i-1];
  }

  // Problem B.1
  cout << value(0,n) << nl;

  // Problem B.2
  ld all = 0;
  for (int i=1; i<=n; i++) {
    all += value(i-1,i);
  }
  cout << all << nl;

  // Problem B.3
  for (int i=0; i<=n; i++) {
    dp[i][i] = 0;
    lopt[i][i] = ropt[i][i] = i;
  }
  for (int l=1; l<=n; l++) {
    for (int i=0; i+l<=n; i++) {
      int x, y;
      x = lopt[i][i+l-1];
      y = lopt[i+1][i+l];
      ld lval = 1e42;
      for (int j=max(i,min(x,y)-MAGIC); j<=min(i+l,max(x,y)+MAGIC); j++) {
        ld cur = get(i,j,i+l);
        if (cur < lval) {
          lval = cur;
          lopt[i][i+l] = j;
        }
      }
      ld rval = 1e42;
      x = ropt[i][i+l-1];
      y = ropt[i+1][i+l];
      for (int j=min(i+l,max(x,y)+MAGIC); j>=max(i,min(x,y)-MAGIC); j--) {
        ld cur = get(i,j,i+l);
        if (cur < rval) {
          rval = cur;
          ropt[i][i+l] = j;
        }
      }
      dp[i][i+l] = min(lval, rval);
    }
  }
  cout << dp[0][n] << nl;

  // Problem B.4
  for (int i=0; i<=n; i++) {
    dp[i][i] = 0;
    lopt[i][i] = ropt[i][i] = i;
  }
  for (int l=1; l<=n; l++) {
    for (int i=0; i+l<=n; i++) {
      int x, y;
      x = lopt[i][i+l-1];
      y = lopt[i+1][i+l];
      ld lval = -1;
      for (int j=max(i,min(x,y)-MAGIC); j<=min(i+l,max(x,y)+MAGIC); j++) {
        ld cur = get(i,j,i+l);
        if (cur > lval) {
          lval = cur;
          lopt[i][i+l] = j;
        }
      }
      ld rval = -1;
      x = ropt[i][i+l-1];
      y = ropt[i+1][i+l];
      for (int j=min(i+l,max(x,y)+MAGIC); j>=max(i,min(x,y)-MAGIC); j--) {
        ld cur = get(i,j,i+l);
        if (cur > rval) {
          rval = cur;
          ropt[i][i+l] = j;
        }
      }
      dp[i][i+l] = max(lval, rval);
    }
  }
  cout << dp[0][n] << nl;

  return 0;
}
