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
// To find a^{-1} mod m, use egcd(a,m,x,y), then x = a^{-1}
// Returns gcd(a,b)
//*!
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
//*!
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

int a[10][10];

bool valid(int n) {
  //cerr << "VALID " << nl;
  for (int i=0; i<n; i++) {
    int row, col;
    row = col = 0;
    for (int j=0; j<n; j++) {
      //cerr << a[i][j] << " ";
      row += a[i][j];
      col += a[j][i];
    }
    //cerr << nl;
    if (row % n != 0 || col % n != 0) {
      return false;
    }
  }
  return true;
}

bool line(int n, int i) {
  //cerr << "LINE " << i << ": ";
  int sum = 0;
  for (int j=0; j<n; j++) {
    sum += a[i][j];
    //cerr << a[i][j] << " ";
  }
  //cerr << nl;
  return sum % n == 0;
}

Int solve(int n, int i, int j) {
  if (j == n) {
    if (!line(n,i)) return 0;
    else { i++; j=0; }
  }
  if (i == n) {
    return valid(n);
  }

  Int res = 0;
  for (int v=0; v<n; v++) {
    a[i][j] = v;
    res += solve(n, i, j+1);
  }
  return res;
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

  cout << solve(n,0,0) << nl;

  return 0;
}
