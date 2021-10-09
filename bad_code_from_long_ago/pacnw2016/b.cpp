#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;
const int N = 55;
map<char, int> dx = {{'L', 0}, {'R', 0}, {'U', -1}, {'D', 1}};
map<char, int> dy = {{'L', -1}, {'R', 1}, {'U', 0}, {'D', 0}};

int n, m;
int dp[N][N][N];
bool vis[N][N][N];
vector<string> grid;
string command;
inline pair<int, int> move(char mv, int x, int y) {
  int xn = x + dx[mv], yn = y + dy[mv];
  if (xn < 0 || xn >= n || yn < 0 || yn >= m || grid[xn][yn] == '#')
    return {x, y};
  return {xn, yn};
}

int solve(int spos, int x, int y) {
//  cout << x << " " << y << endl;
  if (grid[x][y] == 'E') return 0;
  if (dp[spos][x][y] != -1) return dp[spos][x][y];
  if (vis[spos][x][y]) return INF;
  vis[spos][x][y] = 1;
  // transitions: delete, add, do nothing
  int ans = INF;
  if (spos < command.size()) {
    // nothing
    int xn, yn; tie(xn, yn) = move(command[spos], x, y);
    ans = min(ans, solve(spos+1, xn, yn));
    // delete
    ans = min(ans, solve(spos+1, x, y) + 1);
  }
  // add
  for (char c : {'L', 'R', 'U', 'D'}) {
    int xn, yn; tie(xn, yn) = move(c, x, y);
//    cout << x << " " << y << " " << c << " " << xn << " " << yn << endl;
    if (xn != x || yn != y)
      ans = min(ans, solve(spos, xn, yn) + 1);
  }
  return dp[spos][x][y] = ans;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  cin >> n >> m;
  grid.resize(n);
  for (int i = 0; i < n; i++)
    cin >> grid[i];
  cin >> command;
//  memset(dp, -1, sizeof dp);
  memset(vis, 0, sizeof vis);
  deque<vector<int>> pq;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == 'R') {
//        cout << solve(0, i, j) << endl;
        pq.push_back({0, i, j, 0});
        goto dijk;
      }
dijk:
  while (!pq.empty()) {
    auto v = pq.front(); pq.pop_front();
    int d = v[0], x = v[1], y = v[2], spos = v[3];
    if (grid[x][y] == 'E') {
      cout << d << endl;
      return 0;
    }
    if (vis[spos][x][y]) continue;
    vis[spos][x][y] = 1;
    if (spos < command.size()) {
      int xn, yn; tie(xn, yn) = move(command[spos], x, y);
      pq.push_front({d, xn, yn, spos+1});
      pq.push_back({d+1, x, y, spos+1});
    }
    for (char c : {'L', 'R', 'U', 'D'}) {
      int xn, yn; tie(xn, yn) = move(c, x, y);
      if (!vis[spos][xn][yn])
        pq.push_back({d+1, xn, yn, spos});
    }
  }
  cout << "bad" << endl;
  return 0;
}
