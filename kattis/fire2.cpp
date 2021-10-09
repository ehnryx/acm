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

struct Node {
  int a, b; bool fire;
  int dist;
};

vector<int> dx = {1,-1,0,0};
vector<int> dy = {0,0,1,-1};

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
    int n, m;
    cin >> m >> n;

    string grid[n];
    for (int i=0; i<n; i++) {
      cin >> grid[i];
    }

    queue<Node> bfs;
    for (int i=0; i<n; i++) {
      for (int j=0; j<m; j++) {
        if (grid[i][j] == '*') {
          bfs.push({i,j,1,0});
          grid[i][j] = '.';
        }
      }
    }
    for (int i=0; i<n; i++) {
      for (int j=0; j<m; j++) {
        if (grid[i][j] == '@') {
          bfs.push({i,j,0,0});
          grid[i][j] = '.';
        }
      }
    }

    int ans = 0;
    while (!bfs.empty() && !ans) {
      Node cur = bfs.front();
      bfs.pop();
      if (grid[cur.a][cur.b] == '#' || grid[cur.a][cur.b] == '*') continue;
      if (cur.fire) {
        //cerr << "fire * " << cur.a << " " << cur.b << nl;
        grid[cur.a][cur.b] = '*';
        for (int d=0; d<4; d++) {
          int na = cur.a+dx[d];
          int nb = cur.b+dy[d];
          if (0<=na && na<n && 0<=nb && nb<m) {
            bfs.push({na,nb,1,0});
          }
        }
      }
      else if (grid[cur.a][cur.b] == '.') {
        //cerr << "visit @ " << cur.a << " " << cur.b << nl;
        grid[cur.a][cur.b] = '@';
        for (int d=0; d<4; d++) {
          int na = cur.a+dx[d];
          int nb = cur.b+dy[d];
          if (0<=na && na<n && 0<=nb && nb<m) {
            bfs.push({na,nb,0,cur.dist+1});
          } else {
            ans = cur.dist+1;
            break;
          }
        }
      }
      //cerr << "GRID" << nl; for (int i=0; i<n; i++) {
        //cerr << grid[i] << nl; }
      //cerr << nl;
    }

    if (ans) {
      cout << ans << nl;
    } else {
      cout << "IMPOSSIBLE" << nl;
    }
  }

  return 0;
}
