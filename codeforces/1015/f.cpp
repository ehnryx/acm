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

////////////////////////////////////////////////////////////////////////
// Extended Euclidean Algorithm (UBC)
// egcd(a,b,x,y) calculates x,y such that ax+by=gcd(a,b)
// To find a^{-1} mod m, use egcd(a,m,x,y) and x = a^{-1}
// Returns gcd(a,b)
ll egcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  } else {
    ll d = egcd(b, a%b, y, x);
    y -= x * (a/b);
    return d;
  }
}
//*/

////////////////////////////////////////////////////////////////////////
// Int struct for operations on a prime field (TESTED)
// WARNING: slow
struct Int {
  ll x;
  Int (ll n=0) { x = n % MOD; if (x < 0) x += MOD; }
  operator ll() { return x; }
  Int operator + (const Int& n) const { return Int(x + n.x); }
  Int operator - (const Int& n) const { return Int(x - n.x); }
  Int operator * (const Int& n) const { return Int(x * n.x); }
  Int operator / (const Int& n) const { return Int(x * n.inv()); }
  void operator += (const Int& n) { x = (x + n.x) % MOD; }
  void operator -= (const Int& n) { x = (x + MOD - n.x) % MOD; }
  void operator *= (const Int& n) { x = (x * n.x) % MOD; }
  void operator /= (const Int& n) { x = (x * n.inv()) % MOD; }
  ll inv() const {
    if (x == 0) throw runtime_error("divide by zero");
    ll c, d;
    egcd(x, MOD, c, d);
    return (c < 0) ? c+MOD : c;
  }
};
//*/

const int N = 201;
Int dp[N][N][N]; // [i][open][match]

vector<int> build_fail(const string& s) {
  int n = s.size();
  vector<int> fail(n+1);
  for (int i = 0, j = -1; ; i++, j++) {
    fail[i] = j;
    if (i == n) return fail;
    while (j >= 0 && s[i] != s[j]) {
      j = fail[j];
    }
  }
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

  int n;
  cin >> n;
  n *= 2;

  string s;
  cin >> s;
  int m = s.size();

  vector<int> fail = build_fail(s);

  dp[0][0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= n/2; j++) {
      for (int k = 0; k <= m; k++) {
        // open bracket
        // close bracket
      }
    }
  }

  cout << dp[n][0][m] << nl;

  return 0;
}
