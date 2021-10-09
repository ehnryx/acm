#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 60;
int lleft, rright;
string grid[N];
int empty[N];

void assign(int row, char c) {
  int col = -1;
  int cnt;
  if ((cnt = (grid[row][4] == '-') + (grid[row][6] == '-')) > 0) {
    if (cnt == 2) col = (lleft >= rright ? 4 : 6);
    else col = (grid[row][4] == '-' ? 4 : 6);
  }
  else if ((cnt = (grid[row][2] == '-') + (grid[row][8] == '-')) > 0) {
    if (cnt == 2) col = (lleft >= rright ? 2 : 8);
    else col = (grid[row][2] == '-' ? 2 : 8);
  }
  else if ((cnt = (grid[row][0] == '-') + (grid[row][10] == '-')) > 0) {
    if (cnt == 2) col = (lleft >= rright ? 0 : 10);
    else col = (grid[row][0] == '-' ? 0 : 10);
  }
  else if (grid[row][5] == '-') {
    col = 5;
  }
  else {
    if (grid[row][1] == '-' && grid[row][9] == '-') {
      col = (lleft >= rright ? 1 : 9);
    } else {
      col = (grid[row][1] == '-' ? 1 : 9);
    }
  }

  grid[row][col] = c;
  empty[row]--;
  if (col < 5) lleft--;
  else if (col > 5) rright--;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int r, n;
  cin >> r >> n;

  lleft = rright = 0;
  memset(empty, 0, sizeof empty);
  for (int i = 0; i < r+3; i++) {
    cin >> grid[i];
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == '-') {
        empty[i]++;
        if (j < 5) lleft++;
        else if (j > 5) rright++;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (empty[1] || empty[r/2+2]) {
      if (empty[1] >= empty[r/2+2]) {
        assign(1, i+'a');
      } else {
        assign(r/2+2, i+'a');
      }
    }
    else {
      int best = 0;
      int dist = INF;
      set<int> choices;
      for (int j = 0; j < r+3; j++) {
        if (empty[j] > best) {
          choices.clear();
          best = empty[j];
          dist = min(j, min(abs((r/2+1)-j), abs((r+2)-j)));
        }
        if (empty[j] == best) {
          int cur = min(j, min(abs((r/2+1)-j), abs((r+2)-j)));
          if (cur < dist) {
            choices.clear();
            dist = cur;
          }
          if (cur == dist) {
            choices.insert(j);
          }
        }
      }

      assign(*choices.begin(), i+'a');
    }
  }

  for (int i = 0; i < r+3; i++) {
    cout << grid[i] << nl;
  }

  return 0;
}
