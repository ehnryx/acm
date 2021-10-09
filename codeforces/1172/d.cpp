#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e3+1;
int a[N], b[N];
pii grid[N][N];

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

  FOR(i,1,n) {
    cin >> a[i];
  }
  FOR(i,1,n) {
    cin >> b[i];
  }

  vector<vector<int>> ans;

  FOR(i,1,n) {
    set<pii> path, rev;
    int r = i;
    for (int j=1; j<=n; j++) {
      if (grid[r][j].first) {
        tie(r,j) = grid[r][j];
      } else {
        path.insert(pii(r,j));
      }
    }
    r = a[i];
    for (int j=n; j>=1; j--) {
      if (grid[r][j].first) {
        tie(r,j) = grid[r][j];
      } else {
        rev.insert(pii(r,j));
      }
    }

    int c = i;
    pii p1(0,0), p2(0,0), r1(0,0), r2(0,0);
    for (int j=1; j<=n; j++) {
      if (grid[j][c].first) {
        tie(j,c) = grid[j][c];
      } else {
        if (!p1.first && path.count(pii(j,c))) {
          p1 = pii(j,c);
        }
        if (!r1.first && rev.count(pii(j,c))) {
          r1 = pii(j,c);
        }
      }
    }
    c = b[i];
    for (int j=n; j>=1; j--) {
      if (grid[j][c].first) {
        tie(j,c) = grid[j][c];
      } else {
        if (!r2.first && rev.count(pii(j,c))) {
          r2 = pii(j,c);
        }
        if (!p2.first && path.count(pii(j,c))) {
          p2 = pii(j,c);
        }
      }
    }

    if (p1.first && r1.first && p1 != r1) {
      grid[p1.first][p1.second] = r1;
      grid[r1.first][r1.second] = p1;
      ans.push_back({p1.first, p1.second, r1.first, r1.second});
    }
    if (p2.first && r2.first && p2 != r2 && p2 != p1 && p2 != r1 && r2 != p1 && r2 != r1) {
      grid[p2.first][p2.second] = r2;
      grid[r2.first][r2.second] = p2;
      ans.push_back({p2.first, p2.second, r2.first, r2.second});
    }
  }

  FOR(i,1,n) {
    int r = i;
    for (int j=1; j<=n; j++) {
      if (grid[r][j].first) {
        tie(r,j) = grid[r][j];
      } else {
      }
    }
    if (r != a[i]) {
      cout << -1 << nl;
      return 0;
    }
    int c = i;
    for (int j=1; j<=n; j++) {
      if (grid[j][c].first) {
        tie(j,c) = grid[j][c];
      } else {
      }
    }
    if (c != b[i]) {
      cout << -1 << nl;
      return 0;
    }
  }


  cout << ans.size() << nl;
  for (const vector<int>& v : ans) {
    for (int it : v) {
      cout << it << " ";
    }
    cout << nl;
  }

  return 0;
}
