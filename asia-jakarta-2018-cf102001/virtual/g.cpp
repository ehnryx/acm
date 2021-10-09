#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int N = 505;

bool adj[N][N];
int deg[N];

inline int h(int a, int b) {
  if (a > b) swap(a, b);
  return (a << 10) + b;
}
inline pair<int, int> unh(int x) {
  return {x >> 10, x % (1 << 10)};
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m; cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    adj[u][v] = adj[v][u] = 1;
    deg[u]++;
    deg[v]++;
  }
  int ans = INF;
  while (1) {
    int mxd = -1;
    vector<int> big;
    for (int i = 1; i <= n; i++) {
      for (int j = i+1; j <= n; j++) {
        if (!adj[i][j]) {
          if (deg[i] + deg[j] > mxd) {
            mxd = deg[i] + deg[j];
            big = {h(i, j)};
          } else if (deg[i] + deg[j] == mxd) {
            big.push_back(h(i, j));
          }
        }
      }
    }
    if (mxd == -1) break;
    ans = min(ans, mxd);
    for (int i : big) {
      int u, v; tie(u, v) = unh(i);
      adj[u][v] = adj[v][u] = 1;
      deg[u]++; deg[v]++;
    }
  }
  cout << ans << nl;

  return 0;
}
