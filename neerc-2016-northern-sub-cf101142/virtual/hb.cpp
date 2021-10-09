#include <bits/stdc++.h>
using namespace std;
#define problem_name "hard"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 62;

struct sq {
  int x, y, l;
  sq add(int a, int b) const {
    return sq{x+a, y+b, l};
  }
  friend ostream& operator<<(ostream& out, const sq& s) {
    return out << s.x << "," << s.y << "," << s.l;
  }
};

int dp[N][N], dp2[N][N];
vector<sq> ans[N][N], ans2[N][N];

void upd(int xoff, int yoff, int nx, int ny, vector<sq>& v) {
  for (const sq& s : ans[nx][ny]) {
    v.push_back(s.add(xoff, yoff));
  }
}

int solve(int x, int y) {
  if (dp[x][y] != -1) return dp[x][y];
  if (x == y) {
    ans[x][y] = {sq{0, 0, x}};
    return dp[x][y] = 1;
  }
  // horiz
  int best = INF;
  int bx, by, cx, cy, xoff, yoff;
  for (int i = 1; i < x; i++) {
    int cur = solve(i, y) + solve(x - i, y);
    if (best > cur) {
      best = cur;
      tie(bx, by, cx, cy) = make_tuple(i, y, x-i, y);
      xoff = i;
      yoff = 0;
    }
  }
  for (int i = 1; i < y; i++) {
    int cur = solve(x, i) + solve(x, y - i);
    if (best > cur) {
      best = cur;
      tie(bx, by, cx, cy) = make_tuple(x, i, x, y-i);
      xoff = 0;
      yoff = i;
    }
  }
  ans[x][y] = ans[bx][by];
  upd(xoff, yoff, cx, cy, ans[x][y]);
  return dp[x][y] = best;
}

struct posoff {
  int x, y, xoff, yoff;
};

void upd2(int xoff, int yoff, int nx, int ny, vector<sq>& v) {
  for (const sq& s : ans2[nx][ny]) {
    v.push_back(s.add(xoff, yoff));
  }
}

int cnt = 0;
int solve2(int x, int y) {
  if (!x || !y) return 0;
  if (dp2[x][y] != -1) return dp2[x][y];
  if (x == y) {
    ans2[x][y] = {sq{0, 0, x}};
    return dp2[x][y] = 1;
  }
  int best = solve(x, y);
  sq besti;
  vector<posoff> bestoffs;
  for (int sz = 1; sz <= min(x, y); sz++) {
    for (int nx = 0; nx+sz < x; nx++) {
      for (int ny = 0; ny+sz < y; ny++) {
        int cur = solve2(nx, ny + sz) 
                + solve2(nx + sz, y - ny - sz)
                + solve2(x - nx - sz, y - ny)
                + solve2(x - nx, ny)
                + 1;
        if (best > cur) {
          best = cur;
          besti = sq{nx, ny, sz};
          bestoffs = {{nx, ny + sz, 0, 0},
                      {nx + sz, y - ny - sz, 0, ny + sz},
                      {x - nx - sz, y - ny, nx + sz, ny},
                      {x - nx, ny, nx, 0}};
        }
        cur = solve2(nx + sz, ny)
            + solve2(nx, y - ny)
            + solve2(x - nx, y - ny - sz)
            + solve2(x - nx - sz, ny + sz)
            + 1;
        if (best > cur) {
          best = cur;
          besti = sq{nx, ny, sz};
          bestoffs = {{nx + sz, ny, 0, 0},
                      {nx, y - ny, 0, ny},
                      {x - nx, y - ny - sz, nx, ny + sz},
                      {x - nx - sz, ny + sz, nx + sz, 0}};
        }
      }
    }
  }
  if (bestoffs.empty()) {
    ans2[x][y] = ans[x][y];
  } else {
    cnt++;
    ans2[x][y] = {besti};
    for (const auto& p : bestoffs) {
      upd2(p.xoff, p.yoff, p.x, p.y, ans2[x][y]);
    }
  }
  return dp2[x][y] = best;
}
const int NN = 60;

string get(char c) {
  if (c == '\\') return "\\\\";
  string ret; ret.push_back(c); return ret;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(problem_name ".in", "r", stdin);
  freopen(problem_name ".out", "w", stdout);
#endif

  memset(dp, -1, sizeof dp);
  memset(dp2, -1, sizeof dp2);
  /*
  cout << "const string ans[N][N] = {\n";
  for (int i = 1; i <= NN; i++) {
    cout << "{";
    for (int j = 1; j <= i; j++) {
      solve2(i, j);
      cout << "R\"";
      for (int k = 0; k < ans[i][j].size(); k++) {
        cout << get(ans[i][j][k].x+'0') << get(ans[i][j][k].y+'0') << get(ans[i][j][k].l+'0');
      }
      cout << "\"" << ",}"[j == i];
    }
    cout << ",";
  }
  cerr << cnt << nl;*/
  int T; cin >> T;
  while (T--) {
    int w, h; cin >> w >> h;
    solve2(w, h);
    cout << ans2[w][h].size() << nl;
    for (const sq& s : ans2[w][h]) {
      cout << s.x << " " << s.y << " " << s.l << nl;
    }
  }

  return 0;
}
