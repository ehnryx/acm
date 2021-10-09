#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int r, c, d;
  cin >> r >> c;
  string s;
  string grid[r];
  map<char,int> dist[r][c];
  for (int i = 0; i < r; i++)
    cin >> grid[i];
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      for (int row = 0; row < r; row++) {
        for (int col = 0; col < c; col++) {
          d = abs(row-i) + abs(col-j);
          if (!dist[i][j].count(grid[row][col]))
            dist[i][j].insert(pair<char,int>(grid[row][col],abs(row-i)+abs(col-j)));
          else if (d < dist[i][j][grid[row][col]])
            dist[i][j][grid[row][col]] = d;
        }
      }
    }
  }
  cin >> s;
  for (int i = 0; i < s.size(); i++) {
    ;<F5>
  }

  return 0;
}
