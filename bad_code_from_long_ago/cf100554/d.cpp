#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ ";
  for (const T& it : v) os << it << " ";
  os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

ld memo[51][51][2501];
void init() {
  for (int i = 0; i <= 50; i++) 
    for (int k = 0; k <= 50; k++)
      for (int j = 0; j <= 2500; j++)
        memo[i][k][j] = -1;
}

ld dp(int n, int m, int row, int col, int placed) {
  if (row == n && col == m)
    return 0;
  if (placed > row*col)
    return 0;
  if (memo[row][col][placed] != -1)
    return memo[row][col][placed];

  ld psame = (ld) (row*col - placed) / (m*n - placed);
  ld pboth = (row < n && col < m) * (ld) ((n-row)*(m-col)) / (m*n - placed);
  ld prow = (row < n) * (ld) ((n-row)*col) / (m*n - placed);
  ld pcol = (col < m) * (ld) (row*(m-col)) / (m*n - placed);

  ld res = 1;
  if (psame > 0) res += psame * dp(n, m, row, col, placed+1);
  if (pboth > 0) res += pboth * dp(n, m, row+1, col+1, placed+1);
  if (prow > 0) res += prow * dp(n, m, row+1, col, placed+1);
  if (pcol > 0) res += pcol * dp(n, m, row, col+1, placed+1);
  return memo[row][col][placed] = res;
}

ld solve(int n, int m) {
  init();
  return dp(n, m, 0, 0, 0);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    cout << solve(n, m) << nl;
  }

  return 0;
}
