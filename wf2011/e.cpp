#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef pair<int,int> pii;

const int N = 5e5+1;
const int M = 2e3+2;
const int offset = 1000;
int x[N], y[N];
int pre[M][M];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  for (int dx,dy,n,q, tt=1; cin>>dx>>dy>>n>>q && dx; tt++) {
    for (int i=0; i<n; i++) {
      cin >> x[i] >> y[i];
    }

    cout << "Case " << tt << ":" <<  nl;
    while (q--) {
      memset(pre, 0, sizeof pre);

      int len;
      cin >> len;
      for (int i=0; i<n; i++) {
        int nx = x[i]+y[i];
        int ny = x[i]-y[i]+offset;
        {
          int curx = max(1, nx-len);
          int cury = max(1, ny-len);
          pre[curx][cury] += 1;
        }
        {
          int curx = max(1, nx-len);
          int cury = min(M-2, ny+len) + 1;
          pre[curx][cury] += -1;
        }
        {
          int curx = min(M-2, nx+len) + 1;
          int cury = max(1, ny-len);
          pre[curx][cury] += -1;
        }
        {
          int curx = min(M-2, nx+len) + 1;
          int cury = min(M-2, ny+len) + 1;
          pre[curx][cury] += 1;
        }
      }
      for (int i=1; i<M; i++) {
        for (int j=1; j<M; j++) {
          pre[i][j] += pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
        }
      }

      int bi, bj, best;
      bi = bj = best = -1;
      for (int j=1; j<=dy; j++) {
        for (int i=1; i<=dx; i++) {
          int ni = i+j;
          int nj = i-j+offset;
          //cerr << i << " " << j << " -> " << pre[ni][nj] << nl;
          if (pre[ni][nj] > best) {
            best = pre[ni][nj];
            bi = i;
            bj = j;
          }
        }
      }
      cout << best << " (" << bi << ',' << bj << ")" << nl;;
    }
  }

  return 0;
}
