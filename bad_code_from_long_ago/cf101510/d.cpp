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
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

const int cap = 6;
ll dp[cap][cap][cap];

ll solve(int h, int n, int w) {
  if (h == 1) return max(0, w-n);
  if (dp[h][n][w] == -1) {
    ll res = 0;
    for (int i = 1; i <= min(n, w-1); i++) {
      res += (w-i) * solve(h-1, n-i, i);
    }
    dp[h][n][w] = res;
  }
  return dp[h][n][w];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  memset(dp, -1, sizeof dp);

  for (int h = 1; h < cap; h++) {
    for (int n = 1; n < cap; n++) {
      for (int w = 1; w < cap; w++) {
        cout << h << "," << n << "," << w << " --> " << solve(h, n, w) << nl;
      }
    }
  }
  
  return 0;
}
