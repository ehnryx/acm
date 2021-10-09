#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
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
  for (const T& it : v) os << it << " "; return os;
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

const int N = 104;
int arr[N], goal[N];
char grid[N][N+6];

void caseinit() {
}

void solve() {
  caseinit();

  int n;
  cin >> n;

  for (int i=0; i<n; i++) {
    for (int j=0; j<n+3; j++) {
      grid[i][j] = '.';
    }
  }

  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  if (arr[0] == 0 || arr[n-1] == 0) {
    cout << "IMPOSSIBLE" << nl;
    return;
  }

  int cur = 0;
  for (int i = 0; i < n; i++) {
    while (arr[i]--) {
      goal[cur++] = i;
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    int diff = goal[i]-i;
    ans = max(ans, abs(diff));
    for (int r = 0; r < abs(diff); r++) {
      if (diff<0) grid[r][i-r] = '/';
      else grid[r][i+r] = '\\';
    }
  }
  cout << ans+1 << nl;

  for (int r=0; r<=ans; r++) {
    for (int i=0; i<n; i++) {
      cout << grid[r][i];
    }
    cout << nl;
  }

  return;
}

