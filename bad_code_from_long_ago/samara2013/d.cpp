#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+9;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

// MODINT
template<int MOD> struct ModInt {
  ll x;
  ModInt(ll n=0) { n %= MOD; if (n < 0) n += MOD; x = n; }
  int get() const { return (int) x; }
  ModInt operator + (const ModInt& other) { return ModInt(x + other.x); }
  ModInt operator - (const ModInt& other) { return ModInt(x + MOD - other.x); }
  ModInt operator * (const ModInt& other) { return ModInt(x * other.x); } 
  ModInt& operator += (const ModInt& other) { x = (x + other.x) % MOD; return *this; }
  ModInt& operator -= (const ModInt& other) { x = (x + MOD - other.x) % MOD; return *this; }
  ModInt& operator *= (const ModInt& other) { x = (x * other.x) % MOD; return *this; }
};

// Find x,y such that ax + by = d = gcd(a,b)
// * a^-1 (mod m): if (egcd(a,m,x,y) == 1) return (x+m)%m; else ERROR;
ll egcd(ll a, ll b, ll& x, ll &y) {
  if (!b) {x = 1; y = 0; return a;}//to ensure d>=0: x=sgn(a);y=0;return abs(a);
  ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d; }

#define Int ModInt<MOD>

Int inv[200001];
Int p2[200001];
void init() {
  ll x, y;
  for (ll i = 1; i <= 200000; i++) {
    egcd(i, MOD, x, y);
    inv[i] = Int(x);
  }
  Int curr(1);
  for (ll i = 0; i <= 200000; i++) {
    p2[i] = Int(curr);
    curr *= Int(2);
  }
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  init();

  int n;
  cin >> n;
  Int ans(0);
  Int choose(n);
  for (ll i = 1; i < n; i++) {
    ans += choose * (p2[i] - Int(1));
    choose *= Int(n-i) * inv[i+1];
  }
  cout << ans.get() << endl;

  return 0;
}
