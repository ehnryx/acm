#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 18, M = N*N*2;
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

string grid[N];

inline int get(int x, int y) {
  return N*x + y;
}

int n, m;
int uf[M];
int find(int x) { return x == uf[x] ? x : uf[x] = find(uf[x]); }
void merge(int a, int b) { uf[find(a)] = find(b); }

inline int in(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < m;
}

ll d[M][M];
int dd[M];
int parx[N][N], pary[N][N];
bool vis[M];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  iota(uf, uf + M, 0);
  for (int i = 0; i < M; i++) {
    fill(d[i], d[i] + M, INF);
  }
  cin >> n >> m;
  grid[0] = string(m+2, 'O');
  for (int i = 1; i <= n; i++) {
    string s; cin >> s;
    grid[i] = 'O' + s + 'O';
  }
  grid[n+1] = string(m+2, 'O');
  n += 2; m += 2;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '.') continue;
      for (int k = 0; k < 4; k++) {
        if (!in(i+dx[k], j+dy[k])) continue;
        if (grid[i+dx[k]][j+dy[k]] == grid[i][j]) {
          merge(get(i, j), get(i+dx[k], j+dy[k]));
        }
      }
    }
  }

  set<pair<int, int>> vals;
  int ocean = find(get(0, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] != '.') {
        int root = find(get(i, j));
        if (vis[root]) continue;
        vis[root] = 1;
        queue<pair<int, int>> q;
        d[root][root] = 0;
        for (int x = 0; x < n; x++) {
          for (int y = 0; y < m; y++) {
            if (find(get(x, y)) == root) {
              q.emplace(x, y);
            }
          }
        }
        while (!q.empty()) {
          int x, y; tie(x, y) = q.front(); q.pop();
          for (int k = 0; k < 4; k++) {
            int nx = x+dx[k], ny = y+dy[k];
            if (!in(nx, ny)) continue;
            if (grid[nx][ny] == 'X') continue;
            if (d[root][find(get(nx, ny))] > d[root][find(get(x, y))] + 1) {
              d[root][find(get(nx, ny))] = d[root][find(get(x, y))] + 1;
              q.emplace(nx, ny);
            }
          }
        }
        if (root != ocean) {
          vals.emplace(d[root][ocean], root);
        }
      }
    }
  }

  tuple<ll, int, int, int, int> best;
  get<0>(best) = INF;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < n; k++) {
        for (int l = 0; l < m; l++) {
          if (grid[i][j] != 'X' || grid[k][l] != 'X') {
            continue;
          }
          if (find(get(i, j)) == find(get(k, l))) continue;
          int c1 = find(get(i, j)), c2 = find(get(k, l));
          for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
              if (grid[x][y] != '.') continue;
              int a = get(x, y);
              ll score = d[c1][a] + d[c2][a] + d[ocean][a];
              best = min(best, make_tuple(score, c1, c2, x, y));
            }
          }
        }
      }
    }
  }

  ll s1; int c1, c2, bx, by;
  tie(s1, c1, c2, bx, by) = best;
  //cerr << "score: " << get<0>(best) << nl;
  //cerr << "square: " << bx << " " << by << nl;
  ll s2 = vals.begin()->first + (++vals.begin())->first;
  //cerr << "score2: " << s2 << nl;
  if (s1 < s2) {
    // ans
    queue<pair<int, int>> q;
    q.emplace(bx, by);
    memset(dd, INF, sizeof dd);
    dd[get(bx, by)] = 0;
    auto bfill = [&](int x, int y) {
      int cx = x, cy = y;
      while (tie(cx, cy) != tie(bx, by)) {
        int nx = parx[cx][cy], ny = pary[cx][cy];
        tie(cx, cy) = tie(nx, ny);
        grid[cx][cy] = '*';
      }
    };
    bool fc1 = 0, fc2 = 0, focean = 0;
    while (!q.empty()) {
      int x, y;
      tie(x, y) = q.front(); q.pop();
      if (find(get(x, y)) == c1 && !fc1) {
        fc1 = 1;
        bfill(x, y);
      }
      if (find(get(x, y)) == c2 && !fc2) {
        fc2 = 1;
        bfill(x, y);
      }
      if (grid[x][y] == 'X') continue;
      if (find(get(x, y)) == ocean && !focean) {
        focean = 1;
        bfill(x, y);
      }
      for (int k = 0; k < 4; k++) {
        int nx = x+dx[k], ny = y+dy[k];
        if (!in(nx, ny)) continue;
        //if (grid[nx][ny] == 'X') continue;
        if (dd[get(nx, ny)] > dd[get(x, y)] + 1) {
          dd[get(nx, ny)] = dd[get(x, y)] + 1;
          parx[nx][ny] = x;
          pary[nx][ny] = y;
          q.emplace(nx, ny);
        }
      }
    }
  } else {
    for (int k : {vals.begin()->second, (++vals.begin())->second}) {
      queue<pair<int, int>> q;
      memset(dd, INF, sizeof dd);
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          if (find(get(i, j)) == k) {
            dd[get(i, j)] = 0;
            q.emplace(i, j);
          }
        }
      }
      auto bfill = [&](int x, int y) {
        int cx = x, cy = y;
        while (find(get(cx, cy)) != k) {
          grid[cx][cy] = '*';
          int nx = parx[cx][cy], ny = pary[cx][cy];
          tie(cx, cy) = tie(nx, ny);
        }
      };
      while (!q.empty()) {
        int x, y; tie(x, y) = q.front(); q.pop();
        if (find(get(x, y)) == ocean) {
          bfill(x, y);
          break;
        }
        for (int k = 0; k < 4; k++) {
          int nx = x+dx[k], ny = y+dy[k];
          if (!in(nx, ny)) continue;
          if (grid[nx][ny] == 'X') continue;
          if (dd[get(nx, ny)] > dd[get(x, y)] + 1) {
            dd[get(nx, ny)] = dd[get(x, y)] + 1;
            parx[nx][ny] = x;
            pary[nx][ny] = y;
            q.emplace(nx, ny);
          }
        }
      }
    }
  }
  for (int i = 1; i < n-1; i++) {
    for (int j = 1; j < m-1; j++) {
      cout << grid[i][j];
    }
    cout << nl;
  }
  return 0;
}
