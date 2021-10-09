#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int dist(int a, int b, int c, int d) {
  return abs(a-c) + abs(b-d);
}


//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int sx, sy, tx ,ty;
  cin >> sx >> sy;
  cin >> tx >> ty;
  int init = dist(sx, sy, tx, ty);
  if (init == 0) {
    cout << 0 << nl;
    return 0;
  }

  int n;
  cin >> n;

  int good = 0;
  int dx, dy;
  dx = dy = 0;
  for (int i=1; i<=n; i++) {
    char c;
    cin >> c;
    if (c == 'U') {
      if (dist(sx,sy+1,tx,ty) < dist(sx,sy,tx,ty)) {
        good++;
        sy += 1;
        dy += 1;
        if (dist(sx,sy,tx,ty) <= good) {
          cout << i << nl;
          return 0;
        }
      }
    } else if (c == 'L') {
      if (dist(sx-1,sy,tx,ty) < dist(sx,sy,tx,ty)) {
        good++;
        sx -= 1;
        dx -= 1;
        if (dist(sx,sy,tx,ty) <= good) {
          cout << i << nl;
          return 0;
        }
      }
    } else if (c == 'R') {
      if (dist(sx+1,sy,tx,ty) < dist(sx,sy,tx,ty)) {
        good++;
        sx += 1;
        dx += 1;
        if (dist(sx,sy,tx,ty) <= good) {
          cout << i << nl;
          return 0;
        }
      }
    } else { // c == 'D'
      if (dist(sx,sy-1,tx,ty) < dist(sx,sy,tx,ty)) {
        good++;
        sy -= 1;
        dy -= 1;
        if (dist(sx,sy,tx,ty) <= good) {
          cout << i << nl;
          return 0;
        }
      }
    }
  }

  ll ans = n;
  int far = min(abs(sx-tx)/abs(dx), abs(sy-ty)/abs(dy));
  if (dist(sx+dx*far, dy+dy*far, tx, ty) <= ans + (ll)far*n) {
  } else {
  }

  return 0;
}
