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




int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int grid[101][101];

  int T;
  cin >> T;
  while (T--) {
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> grid[i][j];
      }
    }

    int bound = 0;

    int prev;
    for (int i = 0; i < n; i++) {
      prev = 0;
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == 0) {
          bound = max(bound, j-prev);
          prev = j+1;
        }
      }
      bound = max(bound, m-prev);
    }

    for (int j = 0; j < m; j++) {
      prev = 0;
      for (int i = 0; i < n; i++) {
        if (grid[i][j] == 0) {
          bound = max(bound, i-prev);
          prev = i+1;
        }
      }
      bound = max(bound, n-prev);
    }

    if (bound > k) {
      cout << "NO" << nl;
    } else {
      cout << "YES" << nl;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          if (grid[i][j] == 0) cout << 0 << " ";
          else cout << 1 + (i+j)%k << " ";
        }
        cout << nl;
      }
    }
  }

  return 0;
}
