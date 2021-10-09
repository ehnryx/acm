#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Node {
  int id; ld dist;
  bool operator < (const Node& o) const {
    return dist > o.dist;
  }
};

ld sqr (const ld& x) { return x*x; }

const int N = 1e3+2;
ld dist[N][N];
int x[N], y[N], r[N];
ld ans[N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int T;
  cin >> T;
  while (T--) {
    int w, n;
    cin >> w;
    cin >> n;
    dist[n][n+1] = dist[n+1][n] = w;
    for (int i=0; i<n; i++) {
      cin >> x[i] >> y[i] >> r[i];
      dist[n][i] = dist[i][n] = max(0, x[i]-r[i]);
      dist[n+1][i] = dist[i][n+1] = max(0, w-(x[i]+r[i]));
      for (int j=0; j<i; j++) {
        dist[i][j] = dist[j][i] = max((ld)0, sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]))-r[i]-r[j]);
      }
    }

    fill(ans, ans+n+2, -2);
    priority_queue<Node> dijk;
    dijk.push({n,0});
    while (!dijk.empty()) {
      Node cur = dijk.top();
      dijk.pop();
      if (ans[cur.id] < -1) {
        ans[cur.id] = cur.dist;
        for (int j=0; j<n+2; j++) {
          if (j != cur.id) {
            dijk.push({j,max(dist[cur.id][j],cur.dist)});
          }
        }
      }
    }
    cout << ans[n+1]/2 << nl;
  }

  return 0;
}
