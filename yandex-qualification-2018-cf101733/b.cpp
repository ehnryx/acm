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

  int a[2*n][n], grid[n][n];
  vector<int> id[n*n+1];

  for (int i=0; i<2*n; i++) {
    for (int j=0; j<n; j++) {
      cin >> a[i][j];
      id[a[i][j]].push_back(i);
    }
  }

  vector<int> vis(2*n, -1);
  int val[2][n*n+1];
  stack<pii> dfs;

  dfs.push(pii(0,0));
  vis[0] = 0;
  while (!dfs.empty()) {
    int i, t;
    tie(i,t) = dfs.top();
    dfs.pop();

    for (int j=0; j<n; j++) {
      for (int x : id[a[i][j]]) {
        if (vis[x] == -1) {
          dfs.push(pii(x,!t));
          vis[x] = !t;
        }
      }
    }
  }

  for (int i=0; i<2*n; i++) {
    for (int j=0; j<n; j++) {
      val[vis[i]][a[i][j]] = j;
    }
  }

  for (int i=1; i<=n*n; i++) {
    grid[val[0][i]][val[1][i]] = i;
  }

  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      cout << grid[i][j] << " ";
    }
  }
  cout << nl;

  return 0;
}
