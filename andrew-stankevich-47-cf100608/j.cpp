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

const int N = 2000;
string grid[N+1];
int n, m;

int check(int x, int y) {
  int res = 0;

  if (x > 0 && grid[x-1][y] == '#') {
  }

  if (y > 0 && grid[x][y-1] == '#') {
  }

  if (x+1<n && grid[x+1][y] == '#') {
  }

  if (y+1<m && grid[x][y+1] == '#') {
  }

  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  for(;;) {
    cin >> n >> m;
    if (n == 0) break;

    int left, right, top, bottom;
    left = top = INF;
    right = bottom = -INF;
    for (int i = 0; i < n; i++) {
      cin >> grid[i];
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == '#') {
          left = min(left, j);
          right = max(right, j);
          top = min(top, i);
          bottom = max(bottom, i);
        }
      }
    }

    int first, last;
    int ans = 0;

    // top
    first = INF, last = -INF;
    for (int j = 0; j < m; j++) {
      if (grid[top][j] == '#') {
        first = min(first, j);
        last = max(last, j);
      }
    }
    ans = max(ans, max(check(top, first), check(top, last)));

    // bottom
    first = INF, last = -INF;
    for (int j = 0; j < m; j++) {
      if (grid[bottom][j] == '#') {
        first = min(first, j);
        last = max(last, j);
      }
    }
    ans = max(ans, max(check(bottom, first), check(bottom, last)));

    // left
    first = INF, last = -INF;
    for (int i = 0; i < m; i++) {
      if (grid[i][left] == '#') {
        first = min(first, i);
        last = max(last, i);
      }
    }
    ans = max(ans, max(check(first, left), check(last, left)));

    // right
    first = INF, last = -INF;
    for (int i = 0; i < m; i++) {
      if (grid[i][right] == '#') {
        first = min(first, i);
        last = max(last, i);
      }
    }
    ans = max(ans, max(check(first, right), check(last, right)));

    cout << ans << nl;
  }

  return 0;
}
