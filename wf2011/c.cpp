#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef pair<int,int> pii;

const int N = 210;
const string id = "WAKJSD";
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
bool grid[N][N];
bool vis[N][N];

int n, m;
int to_bits(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  return c - 'a' + 10;
}

inline bool in(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < m; 
}

vector<pair<int, int>> comp;
void dfs(int x, int y, int wall) {
  comp.emplace_back(x, y);
  vis[x][y] = 1;
  for (int i = 0; i < 4; i++) {
    if (!in(x+dx[i], y+dy[i])) continue;
    if (vis[x+dx[i]][y+dy[i]]) continue;
    if (grid[x+dx[i]][y+dy[i]] == wall) continue;
    dfs(x+dx[i], y+dy[i], wall);
  }
}

void print() {
  return;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (vis[i][j]) cerr << 'V';
      else cerr << grid[i][j];
    }
    cerr << nl;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int h, w;
  int tt = 1;
  while (cin >> h >> w) {
    if (!h) break;
    cout << "Case " << tt++ << ": ";
    memset(grid, 0, sizeof grid);
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        char c; cin >> c;
        int x = to_bits(c);
        for (int k = 0, bit = (1 << 3); k < 4; k++, bit >>= 1) {
          grid[i+1][4*j+k+1] = (x & bit) != 0;
        }
      }
    }
    n = h+2;
    m = 4*w+2;
    dfs(0, 0, 1);
    string ans;
    for (int i = 1; i < n-1; i++) {
      for (int j = 1; j < m-1; j++) {
        if (vis[i][j]) continue;
        if (grid[i][j] == 1) {
          comp.clear();
          print();
          dfs(i, j, 0);
          print();
          int holes = 0;
          for (const auto& p : comp) {
            for (int k = 0; k < 4; k++) {
              if (!in(p.first+dx[k], p.second+dy[k])) continue;
              if (vis[p.first+dx[k]][p.second+dy[k]]) continue;
              if (grid[p.first+dx[k]][p.second+dy[k]] == 1) continue;
              holes++;
              dfs(p.first+dx[k], p.second+dy[k], 1);
            }
          }
          ans.push_back(id[holes]);
        }
      }
    }
    sort(ans.begin(), ans.end());
    cout << ans << nl;
  }

  return 0;
}
