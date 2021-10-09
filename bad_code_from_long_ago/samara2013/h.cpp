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
const ll MOD = 1e9+7;
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

ldouble dist(ldouble a, ldouble b, ldouble x, ldouble y) {
  return sqrt((a-x)*(a-x) + (b-y)*(b-y));
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  ldouble a[3], b[3], x[3], y[3];
  for (int i = 0; i < 3; i++)
    cin >> a[i] >> b[i];
  for (int i = 0; i < 3; i++)
    cin >> x[i] >> y[i];
  vector<ldouble> da(3), dx(3);
  for (int i = 0; i < 3; i++) 
    da[i] = dist(a[i], b[i], a[(i+1)%3], b[(i+1)%3]);
  for (int i = 0; i < 3; i++) 
    dx[i] = dist(x[i], y[i], x[(i+1)%3], y[(i+1)%3]);
  sort(da.begin(), da.end());
  sort(dx.begin(), dx.end());
  ldouble scale = da[0]/dx[0];
  for (int i = 0; i < 3; i++) {
    if (abs(da[i]/dx[i] - scale) > 1e-9) {
      cout << "NO" << endl;
      return 0;
    }
  }
  cout << "YES" << endl;
  return 0;
}
