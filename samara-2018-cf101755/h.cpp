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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m, d;
  cin >> n >> m >> d;

  pii source, sink;
  string grid[n];
  int nw[n][m], ne[n][m], sw[n][m], se[n][m];
  memset(nw, 0, sizeof nw);
  memset(ne, 0, sizeof ne);
  memset(sw, 0, sizeof sw);
  memset(se, 0, sizeof se);
  for (int i = 0; i < n; i++) {
    cin >> grid[i];
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'S') {
        source = pii(i,j);
      } else if (grid[i][j] == 'F') {
        sink = pii(i,j);
      } else if (grid[i][j] == 'M') {
        nw[i][j] = d;
        ne[i][j] = d;
        sw[i][j] = d;
        se[i][j] = d;
      }
    }
  }

  for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < m-1; j++) {
      if (ne[i][j]) {
        grid[i+1][j] = grid[i][j+1] = 'M';
        ne[i+1][j] = max(ne[i+1][j], ne[i][j]-1);
        ne[i][j+1] = max(ne[i][j+1], ne[i][j]-1);
      }
    }
  }

  for (int i = 0; i < n-1; i++) {
    for (int j = m-1; j > 0; j--) {
      if (se[i][j]) {
        grid[i+1][j] = grid[i][j-1] = 'M';
        se[i+1][j] = max(se[i+1][j], se[i][j]-1);
        se[i][j-1] = max(se[i][j-1], se[i][j]-1);
      }
    }
  }

  for (int i = n-1; i > 0; i--) {
    for (int j = 0; j < m-1; j++) {
      if (nw[i][j]) {
        grid[i-1][j] = grid[i][j+1] = 'M';
        nw[i-1][j] = max(nw[i-1][j], nw[i][j]-1);
        nw[i][j+1] = max(nw[i][j+1], nw[i][j]-1);
      }
    }
  }

  for (int i = n-1; i > 0; i--) {
    for (int j = m-1; j > 0; j--) {
      if (sw[i][j]) {
        grid[i-1][j] = grid[i][j-1] = 'M';
        sw[i-1][j] = max(sw[i-1][j], sw[i][j]-1);
        sw[i][j-1] = max(sw[i][j-1], sw[i][j]-1);
      }
    }
  }

  //cerr << "GRID: " << nl; for (int i = 0; i < n; i++) cerr << grid[i] << nl; cerr << nl;

  int dist[n][m]; memset(dist, -1, sizeof dist);
  queue<pii> next;
  next.push(source);
  dist[source.first][source.second] = 0;
  while (!next.empty()) {
    pii cur = next.front();
    next.pop();
    if (cur == sink) break;
    if (grid[cur.first][cur.second] == 'M') continue;

    if (cur.first > 0 && dist[cur.first-1][cur.second] == -1) {
      dist[cur.first-1][cur.second] = dist[cur.first][cur.second]+1;
      next.push(pii(cur.first-1, cur.second));
    }
    if (cur.second > 0 && dist[cur.first][cur.second-1] == -1) {
      dist[cur.first][cur.second-1] = dist[cur.first][cur.second]+1;
      next.push(pii(cur.first, cur.second-1));
    }
    if (cur.first < n-1 && dist[cur.first+1][cur.second] == -1) {
      dist[cur.first+1][cur.second] = dist[cur.first][cur.second]+1;
      next.push(pii(cur.first+1, cur.second));
    }
    if (cur.second < m-1 && dist[cur.first][cur.second+1] == -1) {
      dist[cur.first][cur.second+1] = dist[cur.first][cur.second]+1;
      next.push(pii(cur.first, cur.second+1));
    }
  }

  if (grid[sink.first][sink.second] == 'M') cout << -1 << nl;
  else cout << dist[sink.first][sink.second] << nl;

  return 0;
}
