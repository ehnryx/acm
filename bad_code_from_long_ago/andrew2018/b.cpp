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

  int n, m;
  cin >> n >> m;
  if (m < n) {
    cout << "VANCOUVER" << nl;
    return 0;
  }

  int deg[n];
  for (int i = 0; i < n; i++) {
    cin >> deg[i];
    if (deg[i] == 0) {
      cout << "VANCOUVER" << nl;
      return 0;
    }
  }

  sort(deg, deg+n);
  for (int i = 0; i < n; i++) {
    if (deg[i] <= i) {
      cout << "UNCERTAIN" << nl;
      return 0;
    }
  }

  cout << "BROOKLYN" << nl;

  return 0;
}
