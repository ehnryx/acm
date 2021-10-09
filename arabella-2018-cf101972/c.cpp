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

ld sqr(ld x) { return (ld)x*x; }

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int T;
  cin >> T;
  while (T--) {
    ld a, b, c, x;
    cin >> a >> b >> c >> x;
    ld first = sqrt(sqr(b+c+c)+sqr(a));
    ld dist = sqrt(sqr(a)+sqr(b));
    ld second = dist*((ld)x/100) + sqrt(sqr(b*(1-(ld)x/100)+c+c)+sqr(a*(1-(ld)x/100)));
    cout << first+second << nl;
  }

  return 0;
}
