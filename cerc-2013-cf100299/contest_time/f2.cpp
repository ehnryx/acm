#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
const int N = 10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int dx[] = {2, -2}, dy[] = {2, 2};

struct edge {
  int x, y, i;
};

vector<string> grid(10);

vector<edge> adj[N][N];
char dp[N][N][1 << 16];
void build(int k) {
  int m = 0;
  //cerr << "# " << k << endl;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      switch (k) {
      case 0: if (!(i%2 == 0 && (i/2+j/2)%2 == 0)) goto end;
          break;
      case 1: if (!(i%2 == 0 && (i/2+j/2)%2)) goto end;
          break;
      case 2: if (!(i%2 && (i/2+j/2)%2 == 0)) goto end;
          break;
      case 3: if (!(i%2 && (i/2+j/2)%2)) goto end;
          break;
      }
      for (int l = 0; l < 2; l++) {
        if (i+dx[l] < 0 || i+dx[l] >= N || j+dy[l] < 0 || j+dy[l] >= N) continue;
        if ((grid[i][j] == '#' || grid[i][j] == 'W')
          && (grid[i+dx[l]][j+dy[l]] == '#' || grid[i+dx[l]][j+dy[l]] == 'W')
          && (grid[i+dx[l]/2][j+dy[l]/2] == 'B')) {
          //cerr << "ADD (" << i << " " << j << ") (" << i+dx[l] << " " << j+dy[l] << ")" << endl;
          adj[i][j].push_back({i+dx[l], j+dy[l], m});
          adj[i+dx[l]][j+dy[l]].push_back({i, j, m});
          m++;
        }
      }
end:;
    }
  }
  ////cerr << m << endl;
  assert(m<=16);
}
int solve(char x, char y, int mask) {
  if (dp[x][y][mask] != -1) return dp[x][y][mask];
  int ans = 0;
  for (const edge& e : adj[x][y]) {
    if (mask & (1 << e.i) && grid[e.x][e.y] != 'W') {
      ans = max(ans, solve(e.x, e.y, mask ^ (1 << e.i)) + 1);
    }
  }
  return dp[x][y][mask] = ans;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T; cin >> T;
  while (T--) {
    for (int i = 0; i < N; i++) cin >> grid[i];
    int ans = 0;
    for (int k = 0; k < 4; k++) {
      memset(dp, -1, sizeof dp);
      for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) adj[i][j].clear();
      build(k);
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          switch (k) {
          case 0: if (!(i%2 == 0 && (i/2+j/2)%2 == 0)) continue;
              break;
          case 1: if (!(i%2 == 0 && (i/2+j/2)%2)) continue;
              break;
          case 2: if (!(i%2 && (i/2+j/2)%2 == 0)) continue;
              break;
          case 3: if (!(i%2 && (i/2+j/2)%2)) continue;
              break;
          }
          if (grid[i][j] == 'W') {
            grid[i][j] = '.';
            ans = max(ans, (int) solve(i, j, (1 << 16) - 1));
            grid[i][j] = 'W';
          }
        }
      }
    }
    cout << ans << nl;
  }
  cerr << (ld)clock() / CLOCKS_PER_SEC << endl;
  return 0;
}
