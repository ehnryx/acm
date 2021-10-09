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

vector<int> dx = { 0, 0, 1, -1 };
vector<int> dy = { 1, -1, 0, 0 };

const int N = 50;
string grid[N];
bool vis[N][N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;

  for (int i=0; i<n; i++) {
    cin >> grid[i];
  }

  function<bool(int,int,char)> loglog = [&] (int s, int t, char c) {
    memset(vis, 0, sizeof vis);
    grid[s][t] = c;
    int groups = 0;
    for (int i=0; i<n; i++) {
      for (int j=0; j<m; j++) {
        if (grid[i][j] == '.' && !vis[i][j]) {
          if (++groups > 1) return false;
          queue<pii> bfs;
          bfs.push(pii(i,j));
          vis[i][j] = true;
          while (!bfs.empty()) {
            int x, y;
            tie(x,y) = bfs.front();
            bfs.pop();
            for (int d=0; d<4; d++) {
              int nx = x+dx[d];
              int ny = y+dy[d];
              if (0<=nx && nx<n && 0<=ny && ny<m && !vis[nx][ny] && grid[nx][ny]!='#') {
                bfs.push(pii(nx,ny));
                vis[nx][ny] = true;
              }
            }
          }
        }
      }
    }
    grid[s][t] = '?';
    return true;
  };

  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      if (grid[i][j] == '?') {
        bool land = loglog(i,j,'.');
        bool water = loglog(i,j,'#');
        if (land && water) {
          cout << "Ambiguous" << nl;
          return 0;
        }
        if (!land && !water) {
          cout << "Impossible" << nl;
          return 0;
        }
        if (land) {
          grid[i][j] = '.';
        } else {
          grid[i][j] = '#';
        }
      }
    }
  }

  for (int i=0; i<n; i++) {
    cout << grid[i] << nl;
  }

  return 0;
}
