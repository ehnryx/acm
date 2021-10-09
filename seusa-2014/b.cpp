#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld solve(ld a, ld b, ld c, ld& res) {
  ld cq = (b*b+c*c-a*a)/(2*b*c);
  if (abs(cq) > 1) return false;
  ld q = acos(cq);
  if (q < 0) q += 2*M_PIl;
  if (q > 2*M_PIl/3) return false;
  res += 0.5*b*c*sin(M_PIl/3+q);
  return true;
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  ld a, b, c;
  cin >> a >> b >> c;

  ld ans = 0;
  if (!solve(a, b, c, ans)) {
    cout << -1 << nl;
  } else if (!solve(b, c, a, ans)) {
    cout << -1 << nl;
  } else if (!solve(c, a, b, ans)) {
    cout << -1 << nl;
  } else {
    cout << ans << nl;
  }

  return 0;
}
