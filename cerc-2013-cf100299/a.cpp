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

typedef pair<char,int> Move;
ostream& operator << (ostream& os, const Move& mv) {
  return os << mv.first << mv.second+1;
}

const int N = 100 + 1;
int grid[N][N];
int parity[N][N];

int n, m;
vector<Move> ans;

void reverse_row(int x) {
  ans.push_back(Move('R', x));
  for (int i = 0; i < m/2; i++) {
    swap(grid[x][i], grid[x][m-1-i]);
  }
}
void reverse_col(int x) {
  ans.push_back(Move('C', x));
  for (int i = 0; i < n/2; i++) {
    swap(grid[i][x], grid[n-1-i][x]);
  }
}

void print() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      assert(grid[i][j] == i*m + j+1);
    }
  }

  cout << "POSSIBLE " << ans.size();
  for (const Move& it : ans) {
    cout << " " << it;
  }
  cout << nl;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while (T--) {
    //cerr << "TEST CASE " << endl;

    cin >> n >> m;

    bool impossible = false;
    memset(parity, 0, sizeof parity);
    ans.clear();

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> grid[i][j];
      }
    }

    if (n % 2 == 1) {
      int mid = n/2;
      if (grid[mid][0] > grid[mid][m-1]) {
        reverse_row(mid);
      }
      for (int i = 0; i < m; i++) {
        if (grid[mid][i] != mid*m + i+1) {
          impossible = true;
          break;
        }
      }
      if (impossible) {
        cout << "IMPOSSIBLE" << nl;
        continue;
      }
    }

    if (m % 2 == 1) {
      int mid = m/2;
      if (grid[0][mid] > grid[n-1][mid]) {
        reverse_col(mid);
      }
      for (int i = 0; i < n; i++) {
        if (grid[i][mid] != i*m + mid+1) {
          impossible = true;
          break;
        }
      }
      if (impossible) {
        cout << "IMPOSSIBLE" << nl;
        continue;
      }
    }

    for (int i = 0; i < n/2; i++) {
      for (int j = 0; j < m/2 && !impossible; j++) {
        int a = grid[i][j];
        int b = grid[i][m-1-j];
        int c = grid[n-1-i][j];
        int d = grid[n-1-i][m-1-j];
        if ((a < b && b < c && c < d) || (d < c && c < b && b < a)
            || (a < c && c < d && d < b) || (d < b && b < a && a < c)
            || (a < d && d < b && b < c) || (d < a && a < c && c < b)
            || (c < a && a < b && b < d) || (b < d && d < c && c < a)
            || (c < d && d < a && a < b) || (b < a && a < d && d < c)
            || (c < b && b < d && d < a) || (b < c && c < a && a < d)) {
          parity[i][j] = 0;
        }
        else {
          parity[i][j] = 1;
        }
        vector<int> sorted({a, b, c, d});
        sort(sorted.begin(), sorted.end());
        if (sorted[0] != i*m + j+1 
            || sorted[1] != i*m + (m-1-j)+1 
            || sorted[2] != (n-1-i)*m + j+1
            || sorted[3] != (n-1-i)*m + (m-1-j)+1) {
          impossible = true;
          break;
        }
      }
    }
    if (impossible) {
      cout << "IMPOSSIBLE" << nl;
      continue;
    }

    if (n == 1 || m == 1) {
      print();
      continue;
    }

    for (int i = 0; i < n/2; i++) {
      if (parity[i][0]) {
        reverse_row(i);
        for (int j = 0; j < m/2; j++) {
          parity[i][j] ^= 1;
        }
      }
    }
    for (int j = 0; j < m/2; j++) {
      if (parity[0][j]) {
        reverse_col(j);
        for (int i = 0; i < n/2; i++) {
          parity[i][j] ^= 1;
        }
      }
    }

    for (int i = 0; i < n/2; i++) {
      for (int j = 0; j < m/2 && !impossible; j++) {
        if (parity[i][j]) {
          impossible = true;
          break;
        }
      }
    }
    if (impossible) {
      cout << "IMPOSSIBLE" << nl;
      continue;
    }

    for (int i = 0; i < n/2; i++) {
      for (int j = 0; j < m/2; j++) {
        int a = grid[i][j];
        int b = grid[i][m-1-j];
        int c = grid[n-1-i][j];
        int d = grid[n-1-i][m-1-j];

        if (d < c && c < b && b < a) {
          //cerr << "CASE " << d << " < " << c << " < " << b << " < " << a << nl;
          reverse_col(j);
          reverse_row(i);
          reverse_col(j);
          reverse_col(m-1-j);
          reverse_row(i);
          reverse_col(m-1-j);
        }
        else if (a < c && c < d && d < b) {
          //cerr << "CASE " << a << " < " << c << " < " << d << " < " << b << nl;
          reverse_col(m-1-j);
          reverse_row(n-1-i);
          reverse_col(m-1-j);
          reverse_row(n-1-i);
        }
        else if (d < b && b < a && a < c) {
          //cerr << "CASE " << d << " < " << b << " < " << a << " < " << c << nl;
          reverse_col(j);
          reverse_row(n-1-i);
          reverse_col(j);
          reverse_row(n-1-i);
        }
        else if (a < d && d < b && b < c) {
          //cerr << "CASE " << a << " < " << d << " < " << b << " < " << c << nl;
          reverse_row(n-1-i);
          reverse_col(m-1-j);
          reverse_row(n-1-i);
          reverse_col(m-1-j);
        }
        else if (d < a && a < c && c < b) {
          //cerr << "CASE " << d << " < " << a << " < " << c << " < " << b << nl;
          reverse_row(i);
          reverse_col(m-1-j);
          reverse_row(i);
          reverse_col(m-1-j);
        }
        else if (c < a && a < b && b < d) {
          //cerr << "CASE " << c << " < " << a << " < " << b << " < " << d << nl;
          reverse_col(j);
          reverse_row(i);
          reverse_col(j);
          reverse_row(i);
        }
        else if (b < d && d < c && c < a) {
          //cerr << "CASE " << b << " < " << d << " < " << c << " < " << a << nl;
          reverse_col(m-1-j);
          reverse_row(i);
          reverse_col(m-1-j);
          reverse_row(i);
        }
        else if (c < d && d < a && a < b) {
          //cerr << "CASE " << c << " < " << d << " < " << a << " < " << b << nl;
          reverse_row(n-1-i);
          reverse_col(j);
          reverse_row(n-1-i);
          reverse_col(j);
          reverse_col(m-1-j);
          reverse_row(n-1-i);
          reverse_col(m-1-j);
          reverse_row(n-1-i);
        }
        else if (b < a && a < d && d < c) {
          //cerr << "CASE " << b << " < " << a << " < " << d << " < " << c << nl;
          reverse_col(m-1-j);
          reverse_row(i);
          reverse_col(m-1-j);
          reverse_row(i);
          reverse_row(n-1-i);
          reverse_col(m-1-j);
          reverse_row(n-1-i);
          reverse_col(m-1-j);
        }
        else if (c < b && b < d && d < a) {
          //cerr << "CASE " << c << " < " << b << " < " << d << " < " << a << nl;
          reverse_row(n-1-i);
          reverse_col(j);
          reverse_row(n-1-i);
          reverse_col(j);
        }
        else if (b < c && c < a && a < d) {
          //cerr << "CASE " << b << " < " << c << " < " << a << " < " << d << nl;
          reverse_row(i);
          reverse_col(j);
          reverse_row(i);
          reverse_col(j);
        }
      }
    }
    print();
  }

  return 0;
}
