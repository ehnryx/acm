#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

int m, n;
char grid[35][35];
ll dp[35][35];
ll solve(int i, int j) {
  if (i == 0 && j == n)
    return 1;
  if (grid[i][j] == 'B')
    return 0;
  if (i > 0 && j > 0 && grid[i-1][j-1] == 'R')
    return 0;
  if (dp[i][j] == 0) {
    if (i > 0) dp[i][j] += solve(i-1, j);
    if (j < n) dp[i][j] += solve(i, j+1);
  }
  return dp[i][j];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  memset(grid, 0, sizeof(grid));
  memset(dp, 0, sizeof(dp));

  scanf("%d %d", &m, &n);
  for (int i = 0; i < m; i++) {
    scanf("%s", grid[i]);
    for (int j = 0; j < n; j++) {
      if ((j > 0 && grid[i][j-1] == 'R') || (i > 0 && grid[i-1][j] == 'R')) {
        if (grid[i][j] == 'B') {
          cout << 0 << nl;
          return 0;
        }
        grid[i][j] = 'R';
      }
    }
  }
  for (int i = m-1; i >= 0; i--) {
    for (int j = n-1; j >= 0; j--) {
      if ((j < n-1 && grid[i][j+1] == 'B') || (i < m-1 && grid[i+1][j] == 'B')) {
        grid[i][j] = 'B';
      }
    }
  }
  cout << solve(m, 0) << nl;

  return 0;
}
