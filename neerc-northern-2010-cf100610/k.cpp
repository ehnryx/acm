#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
typedef long long ll;
typedef long double ld;
const char nl = '\n';
const ld INF = 1e5;

#define FILE "kitchen"

struct pt {
  ld x, y;
  pt() {}
  pt(ld a, ld b) : x(a), y(b) {}
  pt flipX(const ld P) const {
    return pt(P - (x-P), y);
  }
  pt flipY(const ld P) const {
    return pt(x, P - (y-P));
  }
  pt operator- (const pt& o) const {
    return pt(x-o.x, y-o.y);
  }
  ld len() const {
    return sqrt(x*x+y*y);
  }
};

const int N = 20;
ld dist[N][N];
ld f[N][1<<18];
ld far[N];
pt pts[N];
int W, L, n;

pt probot;

int main() {
  if (fopen(FILE ".in", "r")) {
    freopen(FILE ".in", "r", stdin);
    freopen(FILE ".out", "w", stdout);
  }

  cin >> W >> L;
  cin >> n;
  for (int i=0; i<n; ++i) {
    cin >> pts[i].x >> pts[i].y;
    far[i] = INF;
    far[i] = min(pts[i].x, far[i]);
    far[i] = min(pts[i].y, far[i]);
    far[i] = min(W-pts[i].x, far[i]);
    far[i] = min(L-pts[i].y, far[i]);
  }
  cin >> probot.x >> probot.y;

  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      dist[i][j] = INF;
      dist[i][j] = min((pts[i]-pts[j].flipX(0)).len(), dist[i][j]);
      dist[i][j] = min((pts[i]-pts[j].flipX(W)).len(), dist[i][j]);
      dist[i][j] = min((pts[i]-pts[j].flipY(0)).len(), dist[i][j]);
      dist[i][j] = min((pts[i]-pts[j].flipY(L)).len(), dist[i][j]);
    }
  }

  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      //cerr << "D " << i << " " << j << ": " << dist[i][j] << endl;
    }
  }
  for (int i=0; i<n; ++i) {
    for (int j=0; j<(1<<n); ++j) {
      f[i][j] = INF;
    }
  }

  for (int i=0; i<n; ++i) {
    f[i][1<<i] = (probot - pts[i]).len() + far[i];
  }

  for (int b=0; b<(1<<n); ++b) {
    if (__builtin_popcount(b) < 2) continue;
    for (int i=0; i<n; ++i) {
      if (!((b>>i)&1)) continue;
      int a = b^(1<<i);
      for (int j=0; j<n; ++j) {
        if (!((a>>j)&1)) continue;
        f[i][b] = min(f[i][b], f[j][a] + dist[i][j] - far[j] + far[i]);
      }
    }
  }

  for (int i=0; i<n; ++i) {
    for (int b=0; b<(1<<n); ++b) {
      //cerr << i << " " << bitset<5>(b) << ": " << f[i][b] << endl;
    }
  }


  ld ans = INF;
  for (int i=0; i<n; ++i) {
    ans = min(ans, f[i][(1<<n)-1]);
  }

  cout << fixed << setprecision(15) << ans << endl;

  return 0;
}
