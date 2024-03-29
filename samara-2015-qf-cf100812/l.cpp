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

// Find x,y such that ax + by = d = gcd(a,b)
// * a^-1 (mod m): if (egcd(a,m,x,y) == 1) return (x+m)%m; else ERROR;
ll egcd(ll a, ll b, ll& x, ll &y) {
  if (!b) {x = 1; y = 0; return a;}//to ensure d>=0: x=sgn(a);y=0;return abs(a);
  ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d;
}
// Assuming a != 0, find smallest y >= 0 such that ax + by = c (if possible)
bool canon_egcd(ll a, ll b, ll c, ll& x, ll& y) {
  ll d = egcd(a, b, x, y), z = abs(a/d); if (c%d) return false;
  y = (y*(c/d)%z + z)%z, x = (c - b*y)/a; return true;
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

  ll a, b;
  cin >> a >> b;

  if (min(a, b) == 1) {
    cout << (max(a, b) == 1 ? 1 : 2) << nl;
    return 0; // sad
  }

  ll ans = lcm(a, b);
  if (gcd(a, b) == 1) {
    ll x, y;
    assert(canon_egcd(a, -b, 1 + b, x, y));
    assert(x > 0 && y >= 0);
    ans = min(ans, a * x);
    assert(canon_egcd(b, -a, 1 + a, y, x));
    assert(x >= 0 && y > 0);
    ans = min(ans, b * y);
  }
  cout << ans << nl;

  return 0;
}
