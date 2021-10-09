#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const char nl = '\n';
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

const int N = 15;
ll f[N][1<<N], g[N][1<<N];
int d[N][N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n;
  cin >> n;
  for (int i=0; i<n; ++i) {
    for (int j=i+1; j<n; ++j) {
      cin >> d[i][j];
      d[j][i] = d[i][j];
    }
  }

  int all = (1<<n)-1;
  for(int b=1; b<1<<n; b++) {
    int cnt = __builtin_popcount(b);
    for(int i=all^b; i; i-=i&-i) {
      int u = __builtin_ctz(i);
      g[u][b] = INFLL;
      for(int j=b; j; j-=j&-j) {
        int v = __builtin_ctz(j);
        g[u][b] = min(g[u][b], (ll)d[u][v]*cnt*(n-cnt) + f[v][b^1<<v]);
      }
      f[u][b] = INFLL;
      for(int a=b; a; a=(a-1)&b) {
        f[u][b] = min(f[u][b], g[u][a] + f[u][a^b]);
      }
    }
  }
  cout << f[0][all^1] << nl;

  return 0;
}
