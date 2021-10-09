#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;

vector<int> di = { 0, 0, 1, -1 };
vector<int> dj = { 1, -1, 0, 0 };

const int N = 2e2 + 2;
const int M = 10;
char g[N][N];
int dist[N][N][1<<M];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  fill(&g[0][0], &g[0][0] + N*N, '#');

  int n;
  cin >> n;
  memset(dist, -1, sizeof dist);
  queue<tuple<int,int,int>> bfs;
  for(int i=1; i<=n; i++) {
    cin >> (g[i] + 1);
    for(int j=1; j<=n; j++) {
      if(g[i][j] == '@') {
        dist[i][j][0] = 0;
        bfs.push(make_tuple(i, j, 0));
      }
    }
  }

  while(!bfs.empty()) {
    auto [i, j, bm] = bfs.front();
    bfs.pop();
    if(g[i][j] == '$') {
      cout << dist[i][j][bm] << nl;
      return 0;
    }
    for(int d=0; d<4; d++) {
      int ni = i + di[d];
      int nj = j + dj[d];
      int nbm = bm;
      if(isalpha(g[ni][nj]) && tolower(g[ni][nj]) == g[ni][nj]) {
        nbm |= 1<<(g[ni][nj]-'a');
      }
      if(g[ni][nj] == '#' || dist[ni][nj][nbm] != -1) continue;
      if(isalpha(g[ni][nj]) && toupper(g[ni][nj]) == g[ni][nj]) {
        if(nbm & 1<<(g[ni][nj]-'A')) {
          dist[ni][nj][nbm] = dist[i][j][bm] + 1;
          bfs.push(make_tuple(ni, nj, nbm));
        }
      } else {
        dist[ni][nj][nbm] = dist[i][j][bm] + 1;
        bfs.push(make_tuple(ni, nj, nbm));
      }
    }
  }

  cout << "IMPOSSIBLE" << nl;
  return 0;

  return 0;
}
