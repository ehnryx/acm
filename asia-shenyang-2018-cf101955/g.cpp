#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 6060, K = 1e7+10;

struct d {
  int x, y;
};

vector<d> ds[K];

void pre() {
  int k;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      k = i*i + j*j;
      if (k >= K) break;
      ds[k].push_back({i, j});
      if (i) ds[k].push_back({-i, j});
      if (j) ds[k].push_back({i, -j});
      if (i && j) ds[k].push_back({-i, -j});
    }
  }
}

bitset<N> in[N];
int w[N][N];

inline bool oob(int x, int y) {
  return x < 0 || x >= N || y < 0 || y >= N;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  pre();
  int T; cin >> T;
  for (int tt = 1; tt <= T; tt++) {
    for (int i = 0; i < N; i++) {
      in[i].reset();
    }
    cout << "Case #" << tt << ":\n";
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
      int x, y; cin >> x >> y;
      cin >> w[x][y];
      in[x][y] = 1;
    }
    ll lastans = 0;
    auto upd = [&](int& x, int& y) {
      x = (x + lastans) % 6000 + 1;
      y = (y + lastans) % 6000 + 1;
    };
    for (int i = 0; i < m; i++) {
      int t; cin >> t;
      if (t == 1) {
        int x, y; cin >> x >> y;
        upd(x, y);
        cin >> w[x][y];
        in[x][y] = 1;
      } else if (t == 2) {
        int x, y; cin >> x >> y;
        upd(x, y);
        in[x][y] = 0;
      } else if (t == 3) {
        int x, y, k, dw; cin >> x >> y >> k >> dw;
        upd(x, y);
        for (const d& a : ds[k]) {
          if (oob(x+a.x, y+a.y)) continue;
          if (in[x+a.x][y+a.y]) {
            w[x+a.x][y+a.y] += dw;
          }
        }
      } else if (t == 4) {
        int x, y, k; cin >> x >> y >> k;
        upd(x, y);
        ll ans = 0;
        for (const d& a : ds[k]) {
          if (oob(x+a.x, y+a.y)) continue;
          if (in[x+a.x][y+a.y]) {
            ans += w[x+a.x][y+a.y];
          }
        }
        cout << ans << nl;
        lastans = ans;
      }
    }
  }

  return 0;
}
