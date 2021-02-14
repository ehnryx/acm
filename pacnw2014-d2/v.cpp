#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

bool valid(vector<string>& g) {
  int n = g.size() - 2;
  bool ok = true;
  for(int r=0; r<4; r++) {
    for(int i=1; i<=n && ok; i++) {
      if(g[i][0] == '-') continue;
      int cnt = 0;
      int high = 0;
      for(int j=1; j<=n; j++) {
        if(g[i][j] > high) {
          cnt++;
          high = g[i][j];
        }
      }
      ok &= (cnt == g[i][0] - '0');
    }
    vector<string> rot(n+2);
    for(int i=0; i<=n+1; i++) {
      for(int j=0; j<=n+1; j++) {
        rot[j].push_back(g[n+2-1-i][j]);
      }
    }
    g = move(rot);
  }
  return ok;
}

bool solve(vector<string>& g, int i, int j) {
  int n = g.size() - 2;
  if(j > n) return solve(g, i+1, 1);
  if(i > n) return valid(g);
  if(g[i][j] != '-') return solve(g, i, j+1);
  for(int d=1; d<=n; d++) {
    bool ok = true;
    for(int k=1; k<=n; k++) {
      ok &= (g[k][j] - '0' != d);
      ok &= (g[i][k] - '0' != d);
    }
    if(ok) {
      g[i][j] = d + '0';
      if(solve(g, i, j+1)) {
        return true;
      }
      g[i][j] = '-';
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<string> grid(n+2);
    for(int i=0; i<=n+1; i++) {
      cin >> grid[i];
    }

    if(solve(grid, 1, 1)) {
      for(int i=1; i<=n; i++) {
        cout << grid[i].substr(1, n) << nl;
      }
      cout << nl;
    } else {
      cout << "no" << nl;
      cout << nl;
    }
  }

  return 0;
}
