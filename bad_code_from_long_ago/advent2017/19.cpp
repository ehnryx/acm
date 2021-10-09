#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  string s;

  vector<string> grid;
  while (getline(cin, s)) {
    grid.push_back(s);
  }

  int m = grid[0].size();
  int n = grid.size();
  int start = -1;
  for (int i = 0; i < m; i++) {
    if (grid[0][i] == '|') {
      start = i;
    }
  }

  int x, y;
  x = 0;
  y = start;
  int dirx, diry;
     dirx = 1;
  diry = 0;
  vector<char> ans;
  int count = 0;

  while (!isspace(grid[x][y])) {
    count++;
    if (grid[x][y] == '+') {
      if (dirx == 0) {
        if (x > 0 && grid[x-1][y] == '|') {
          dirx = -1; diry = 0;
        } else {
          dirx = 1; diry = 0;
        }
      }
      else {
        if (y > 0 && grid[x][y-1] == '-') {
          dirx = 0; diry = -1;
        } else {
          dirx = 0; diry = 1;
        }
      }
    }
    else if (isalpha(grid[x][y])) {
      ans.push_back(grid[x][y]);
    }

    x += dirx; y += diry;
  }

  cout << count << nl;

  return 0;
}
