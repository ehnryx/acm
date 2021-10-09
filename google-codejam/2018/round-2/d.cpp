#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<int> pt;
typedef vector<pt> pol;
typedef mt19937 RNG;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T> 
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " ";
  return os;
}
template <class T> 
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; 
  return os << '}';
}
template <class T, class U> 
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) os << it << " ";
  return os << '}';
}

////////////////////////////////////////////////////////////////////////

void solve();
void init() {
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    solve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

const int N = 20;
string grid[N];

void caseinit() {
}

int count(int,int,char,char,char,char);

int n, m;
void solve() {
  caseinit();

  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    cin >> grid[i];
  }

  bool b_nw, b_ne, b_sw, b_se;
  bool w_nw, w_ne, w_sw, w_se;
  bool slash, backslash;
  b_nw = b_ne = b_sw = b_se = w_nw = w_ne = w_sw = w_se = slash = backslash = false;
  for (int i=1; i<n; i++) {
    for (int j=1; j<m; j++) {
      slash |= grid[i-1][j-1] == 'W' && grid[i][j] == 'W' && grid[i-1][j] == 'B' && grid[i][j-1] == 'B';
      backslash |= grid[i-1][j-1] == 'B' && grid[i][j] == 'B' && grid[i-1][j] == 'W' && grid[i][j-1] == 'W';

      b_nw |= grid[i-1][j-1] == 'B' && grid[i-1][j] == 'W' && grid[i][j-1] == 'W' && grid[i][j] == 'W';
      b_ne |= grid[i-1][j-1] == 'W' && grid[i-1][j] == 'B' && grid[i][j-1] == 'W' && grid[i][j] == 'W';
      b_sw |= grid[i-1][j-1] == 'W' && grid[i-1][j] == 'W' && grid[i][j-1] == 'B' && grid[i][j] == 'W';
      b_se |= grid[i-1][j-1] == 'W' && grid[i-1][j] == 'W' && grid[i][j-1] == 'W' && grid[i][j] == 'B';
                                                                               
      w_nw |= grid[i-1][j-1] == 'W' && grid[i-1][j] == 'B' && grid[i][j-1] == 'B' && grid[i][j] == 'B';
      w_ne |= grid[i-1][j-1] == 'B' && grid[i-1][j] == 'W' && grid[i][j-1] == 'B' && grid[i][j] == 'B';
      w_sw |= grid[i-1][j-1] == 'B' && grid[i-1][j] == 'B' && grid[i][j-1] == 'W' && grid[i][j] == 'B';
      w_se |= grid[i-1][j-1] == 'B' && grid[i-1][j] == 'B' && grid[i][j-1] == 'B' && grid[i][j] == 'W';
    }
  }

  int ans = 0;

  for (int r=0; r<=n; r++) {
    ans = max(ans, count(r,0,'B','B','W','W'));
    ans = max(ans, count(r,0,'W','W','B','B'));
  }

  for (int c=0; c<=m; c++) {
    ans = max(ans, count(0,c,'B','W','B','W'));
    ans = max(ans, count(0,c,'W','B','W','B'));
  }

  for (int r=0; r<=n; r++) {
    for (int c=0; c<=m; c++) {
      if (b_nw) ans = max(ans, count(r,c,'B','W','W','W'));
      if (b_ne) ans = max(ans, count(r,c,'W','B','W','W'));
      if (b_sw) ans = max(ans, count(r,c,'W','W','B','W'));
      if (b_se) ans = max(ans, count(r,c,'W','W','W','B'));

      if (w_nw) ans = max(ans, count(r,c,'W','B','B','B'));
      if (w_ne) ans = max(ans, count(r,c,'B','W','B','B'));
      if (w_sw) ans = max(ans, count(r,c,'B','B','W','B'));
      if (w_se) ans = max(ans, count(r,c,'B','B','B','W'));

      if (slash) ans = max(ans, count(r,c,'W','B','B','W'));
      if (backslash) ans = max(ans, count(r,c,'B','W','W','B'));
    }
  }

  cout << ans << nl;

  return;
}

bool correct(int i, int j, int r, int c, char nw, char ne, char sw, char se) {
  if (i<r && j<c) return grid[i][j] == nw;
  if (i<r) return grid[i][j] == ne;
  if (j<c) return grid[i][j] == sw;
  else return grid[i][j] == se;
}

bool vis[N][N];

int count(int r, int c, char nw, char ne, char sw, char se) {
  memset(vis, 0, sizeof vis);
  int res = 0;

  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      if (!vis[i][j]) {
        int cnt = 0;
        stack<pt> dfs;

        if (correct(i,j,r,c,nw,ne,sw,se)) dfs.push(pt(i,j));
        vis[i][j] = true;

        while (!dfs.empty()) {
          pt cur = dfs.top(); dfs.pop();
          cnt++;
          pt dir = 1;
          for (int rot=0; rot<4; rot++) {
            pt nxt = cur+dir;
            int ni = nxt.real();
            int nj = nxt.imag();

            if (0<=ni && ni<n && 0<=nj && nj<m && !vis[ni][nj]) {
              if (correct(ni,nj,r,c,nw,ne,sw,se)) dfs.push(pt(ni,nj));
              vis[ni][nj] = true;
            }

            dir *= pt(0,1);
          }
        }

        res = max(res, cnt);
      }
    }
  }

  //cerr << pii(r,c) << ": " << nw << ne << sw << se << ": " << res << nl;
  return res;
}
