#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

/**
 * Automatically mods everything by MOD
 *
 * egcd(a,b,x,y) calculates x,y that satisfy ax+by=gcd(a,b)
 * to find a^-1 mod m use egcd(a,b,x,y) and x = a^-1
 * egcd also returns the gcd of a and b
 */
ll egcd(ll a, ll b, ll& x, ll& y) {
  if (b == 0) { x = 1, y = 0; return a; }
  ll d = egcd(b, a%b, y, x);
  y -= x * (a/b);
  return d;
}
struct Int {
  ll x;
  Int(ll n=0) { x = n % MOD; if (x < 0) x += MOD; }
  operator ll&() { return x; }
  Int operator + (const Int& n) { return Int(x + n.x); }
  Int operator - (const Int& n) { return Int(x - n.x); }
  Int operator * (const Int& n) { return Int(x * n.x); }
  Int operator / (const Int& n) { return Int(x * n.inverse()); }
  Int& operator += (const Int& n) { x = (x + n.x) % MOD; return *this; }
  Int& operator -= (const Int& n) { x = (x + MOD - n.x) % MOD; return *this; }
  Int& operator *= (const Int& n) { x = (x * n.x) % MOD; return *this; }
  Int& operator /= (const Int& n) { x = (x * n.inverse()) % MOD; return *this; }
  ll inverse() const {
    if (x == 0) throw runtime_error("divide by zero");
    ll c, d;
    egcd(x, MOD, c, d);
    return (c+MOD) % MOD;
  }
};
ostream& operator << (ostream& os, const Int& n) { os << n.x; return os; }

const int N = 2e5+1;
Int power[N];
Int fact[N];
Int invf[N];

void init() {
  power[0] = fact[0] = invf[0] = 1;
  for (int i = 1; i < N; i++) {
    fact[i] = fact[i-1] * Int(i);
    invf[i] = Int(1)/fact[i];
    power[i] = power[i-1]/Int(2);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    n = abs(n);

    if (m < n || m % 2 != n % 2) {
      cout << 0 << nl;
    }
    else {
      int d = (m-n)/2;
      cout << power[m] * fact[m] * invf[d] * invf[m-d] << nl;
    }
  }

  return 0;
}
