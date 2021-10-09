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

const int N = 1e3 + 2;
string grid[3];
Int dp[3][N][2];
// 0: horizontal
// 1: vertical

void caseinit() {
  memset(dp, 0, sizeof dp);
}

void solve() {
  caseinit();

  int n;
  cin >> n;

  for (int i = 0; i < 3; i++) {
    cin >> grid[i];
  }

  if (grid[0][0] == '.') dp[0][0][0] = 1;
  for (int j = 0; j < n; j++) {
    if (grid[1][j] == '.') dp[1][j][1] = dp[0][j][0] + dp[2][j][0];
    if (grid[0][j] == '.') dp[0][j][1] = dp[1][j][0];
    if (grid[2][j] == '.') dp[2][j][1] = dp[1][j][0];
    for (int i = 0; i < 3; i++) {
      if (j+1 == n || grid[i][j+1] == '.') dp[i][j+1][0] = dp[i][j][1];
    }
  }

  cout << dp[2][n][0] << nl;

  return;
}

