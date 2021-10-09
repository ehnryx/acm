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

const int N = 502;
const int L = 10;
int grid[N][N];
int pref[N][N], suff[N][N];

int prmq[N][N][L];
void pbuild(int id) {
  for (int j=1; j<L; j++) for (int i=0; i+(1<<j)-1<N; i++)
    prmq[id][i][j] = max(prmq[id][i][j-1],prmq[id][i+(1<<(j-1))][j-1]);
}
int pquery(int id, int l, int r) {
  if (l>r) swap(l,r);
  int j = 31 - __builtin_clz(r-l+1);
  return max(prmq[id][l][j], prmq[id][r-(1<<j)+1][j]);
}

int srmq[N][N][L];
void sbuild(int id) {
  for (int j=1; j<L; j++) for (int i=0; i+(1<<j)-1<N; i++)
    srmq[id][i][j] = max(srmq[id][i][j-1],srmq[id][i+(1<<(j-1))][j-1]);
}
int squery(int id, int l, int r) {
  if (l>r) swap(l,r);
  int j = 31 - __builtin_clz(r-l+1);
  return max(srmq[id][l][j], srmq[id][r-(1<<j)+1][j]);
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

  int T;
  cin >> T;
  while (T--) {
    memset(pref, 0, sizeof pref);
    memset(suff, 0, sizeof suff);

    int n, m;
    cin >> n >> m;
    for (int i=1; i<=n; i++) {
      pref[i][0] = suff[i][m+1] = 0;
      for (int j=1; j<=m; j++) {
        cin >> grid[i][j];
        pref[i][j] = max(pref[i][j-1], grid[i][j]);
        prmq[j][i][0] = pref[i][j];
      }
      for (int j=m; j>=1; j--) {
        suff[i][j] = max(suff[i][j+1], grid[i][j]);
        srmq[j][i][0] = suff[i][j];
      }
    }
    for (int j=1; j<=m; j++) {
      pbuild(j);
      sbuild(j);
    }

    int ans = INF;
    for (int i=2; i<n; i++) {
      for (int j=2; j<m; j++) {
        int maxv = 0;
        int minv = INF;
        maxv = max(maxv, pquery(j-1,1,i-1));
        minv = min(minv, pquery(j-1,1,i-1));
        maxv = max(maxv, pquery(j-1,n,i+1));
        minv = min(minv, pquery(j-1,n,i+1));
        maxv = max(maxv, squery(j+1,1,i-1));
        minv = min(minv, squery(j+1,1,i-1));
        maxv = max(maxv, squery(j+1,n,i+1));
        minv = min(minv, squery(j+1,n,i+1));
        ans = min(ans, maxv-minv);
      }
    }
    cout << ans << nl;
  }

  return 0;
}
