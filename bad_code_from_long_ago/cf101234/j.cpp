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
  os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
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

  string s;
  cin >> s;
  int n = s.size();

  int zeroes = 0;
  for (char c : s) {
    if (c == '0')
      zeroes++;
  }

  int T;
  cin >> T;
  while (T--) {
    int k;
    cin >> k;

    int cur = 0;
    int ans = 0;
    for (int j = 0; j < n && k >= 0; j++) {
      if (s[j] == '1') {
        k--;
      } else {
        cur++;
      }
      ans = max(ans, cur + k);
    }

    cout << min(ans, zeroes) << nl;
  }

  return 0;
}
