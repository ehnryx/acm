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



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int grid[500][500];
  memset(grid, 0, sizeof(grid));
  int c = 200;
  int cap; cin >> cap;
  grid[c][c] = 1;
  for (int i = 1; i <= cap; i++) {
    for (int j = 0; j < 2*i; j++) {
      grid[c+i][c+i-1-j] = grid[c+i-1][c+i-1-j] + grid[c+i][c+i-1-j+1] + grid[c+i-1][c+i-1-j+1] + grid[c+i-1][c+i-1-j-1];
    }
    for (int j = 0; j < 2*i; j++) {
      grid[c+i-1-j][c-i] = grid[c+i-1-j+1][c-i] + grid[c+i-1-j][c-i+1] + grid[c+i-1-j+1][c-i+1] + grid[c+i-1-j-1][c-i+1];
    }
    for (int j = 0; j < 2*i; j++) {
      grid[c-i][c-i+1+j] = grid[c-i][c-i+1+j-1] + grid[c-i+1][c-i+1+j] + grid[c-i+1][c-i+1+j-1] + grid[c-i+1][c-i+1+j+1];
    }
    for (int j = 0; j < 2*i; j++) {
      grid[c-i+1+j][c+i] = grid[c-i+1+j][c+i-1] + grid[c-i+1+j-1][c+i] + grid[c-i+1+j+1][c+i-1] + grid[c-i+1+j-1][c+i-1];
    }
  }
  int ans = INF;
  for (int j = -cap; j <= cap; j++) {
    for (int i = -cap; i <= cap; i++) {
      cout << grid[c+i][c+j] << " ";
      if (grid[c+i][c+j] > 277678) {
        ans = min(ans, grid[c+i][c+j]);
      }
    }
    cout << nl;
  }
  cout << ans << nl;

  return 0;
}
