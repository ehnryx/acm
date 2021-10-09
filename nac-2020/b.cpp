#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;

const int N = 7;
int len[N];
char g[N][N];
bool pos[N][N];

int solve(int n, int m) {
  if(m == 0) {
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=n; j++) {
        if(g[i][j] == 'O' && !pos[i][j]) {
          return 0;
        }
      }
    }
    return 1;
  }

  int res = 0;

  for(int i=1; i+len[m]-1<=n; i++) {
    for(int j=1; j<=n; j++) {
      bool ok = true;
      for(int k=0; k<len[m]; k++) {
        if(g[i+k][j] == 'X' || pos[i+k][j]) {
          ok = false;
          break;
        }
      }
      if(ok) {
        for(int k=0; k<len[m]; k++) {
          pos[i+k][j] = true;
        }
        res += solve(n, m-1);
        for(int k=0; k<len[m]; k++) {
          pos[i+k][j] = false;
        }
      }
    }
  }

  if(len[m] == 1) return res;

  for(int i=1; i<=n; i++) {
    for(int j=1; j+len[m]-1<=n; j++) {
      bool ok = true;
      for(int k=0; k<len[m]; k++) {
        if(g[i][j+k] == 'X' || pos[i][j+k]) {
          ok = false;
          break;
        }
      }
      if(ok) {
        for(int k=0; k<len[m]; k++) {
          pos[i][j+k] = true;
        }
        res += solve(n, m-1);
        for(int k=0; k<len[m]; k++) {
          pos[i][j+k] = false;
        }
      }
    }
  }

  return res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      cin >> g[i][j];
    }
  }
  for(int i=1; i<=m; i++) {
    cin >> len[i];
  }

  cout << solve(n, m) << nl;

  return 0;
}
