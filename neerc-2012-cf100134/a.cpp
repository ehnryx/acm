#include <bits/stdc++.h>

using namespace std;

const char nl = '\n';
#define FILENAME "addictive"

const int N = 11;
int h,w,c;
int a[N];

int grid[N][N];

int main() {
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  cin >> h >> w >> c;
  for(int i=0;i<c;++i) {
    cin >> a[i];
  }
  int cur = 0;
  for(int row=h; row--;) {
    if (row%2==0) {
      for(int col=0;col < w; col++) {
        grid[row][col] = cur+1;
        if (--a[cur] == 0) cur++;
      }
    } else {
      for(int col=w;col--;) {
        grid[row][col] = cur+1;
        if (--a[cur] == 0) cur++;
      }
    }
  }
  for(int i=0;i<h;++i) {
    for(int j =0;j<w;++j) {
      cout << grid[i][j];
    }
    cout << nl;
  }

  return 0;
}
