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

inline ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
inline ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }

inline ld lsp_dist(const pt &a, const pt &b, const pt& p) {
  return dp(b-a, p-a) > 0 && dp(a-b, p-b) > 0 ? 
    abs(cp(b-a, p-a) / abs(b-a)) : min(abs(a-p), abs(b-p));
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
#ifdef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  cout << fixed << setprecision(3);

  vector<pt> hull;
  int x, y;
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    hull.push_back(pt(x,y));
  }

  if (m+k == n+2) {
    ld ans = INF;
    for (int i = 0; i < n; i++) {
      ans = min(ans, abs(hull[i] - hull[(i+m-1)%n]));
    }
    cout << ans << nl;
  }

  else if (m+k == n+3) {
    ld ans = INF;
    for (int i = 0; i < n; i++) {
      ans = min(ans, lsp_dist(hull[i], hull[(i+1)%n], hull[(i+m-1)%n]));
      ans = min(ans, lsp_dist(hull[i], hull[(i+1)%n], hull[(i+k-1)%n]));
    }
    cout << ans << nl;
  }

  else if (m+k == n+4) {
    ld ans = INF;
    for (int i = 0; i < n; i++) {
      ans = min(ans, lsp_dist(hull[i], hull[(i+1)%n], hull[(i+m-1)%n]));
      ans = min(ans, lsp_dist(hull[i], hull[(i+1)%n], hull[(i+m-2)%n]));
      ans = min(ans, lsp_dist(hull[(i+m-1)%n], hull[(i+m-2)%n], hull[i]));
      ans = min(ans, lsp_dist(hull[(i+m-1)%n], hull[(i+m-2)%n], hull[(i+1)%n]));
      ans = min(ans, lsp_dist(hull[i], hull[(i+1)%n], hull[(i+k-1)%n]));
      ans = min(ans, lsp_dist(hull[i], hull[(i+1)%n], hull[(i+k-2)%n]));
      ans = min(ans, lsp_dist(hull[(i+k-1)%n], hull[(i+k-2)%n], hull[i]));
      ans = min(ans, lsp_dist(hull[(i+k-1)%n], hull[(i+k-2)%n], hull[(i+1)%n]));
    }
    cout << ans << nl;
  }

  else {
    cout << -1 << nl;
  }

  return 0;
}
