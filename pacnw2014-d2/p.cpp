#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

bool check(const vector<string>& g, int s) {
  int n = g.size();
  int m = g[0].size();
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      int o = 2*s - i - 1;
      if(o<0 || o>=n) {
        if(g[i][j] == '.') return false;
      } else {
        if(g[i][j] == g[o][j]) return false;
      }
    }
  }
  return true;
}

bool diagonal(const vector<string>& g, int s) {
  int n = g.size();
  int m = g[0].size();
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      if(i+j == s) {
        if(g[i][j] == '.') return false;
      } else {
        int x = i + s - (i+j);
        int y = j + s - (i+j);
        if(x<0 || x>=n || y<0 || y>=m) {
          if(g[i][j] == '.') return false;
        } else {
          if(g[i][j] == g[x][y]) return false;
        }
      }
    }
  }
  return true;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for(int i=0; i<n; i++) {
      cin >> grid[i];
    }

    vector<tuple<int,int,int,int>> ans;
    for(int i=1; i<n; i++) {
      if(check(grid, i)) {
        ans.emplace_back(i, 1, i, m);
      }
    }

    vector<string> rotated(m);
    for(int i=n-1; i>=0; i--) {
      for(int j=0; j<m; j++) {
        rotated[j].push_back(grid[i][j]);
      }
    }
    for(int j=1; j<m; j++) {
      if(check(rotated, j)) {
        ans.emplace_back(1, j, n, j);
      }
    }

    for(int ij=0; ij<n+m-1; ij++) {
      if(diagonal(grid, ij)) {
        ans.emplace_back(
          1 + (ij < n ? ij : n-1),
          1 + (ij < n ? 0 : ij-(n-1)),
          1 + (ij < m ? 0 : ij-(m-1)),
          1 + (ij < m ? ij : m-1));
      }
      if(diagonal(rotated, ij)) {
        ans.emplace_back(
          (ij < n ? n-ij : 1),
          (ij < n ? 1 : ij - (n-1) + 1),
          (ij < m ? n : n - (ij - (m-1))),
          (ij < m ? ij+1 : m));
      }
    }

    auto [a, b, x, y] = *min_element(ans.begin(), ans.end());
    cout << a << " " << b << " " << x << " " << y << nl;
  }

  return 0;
}
