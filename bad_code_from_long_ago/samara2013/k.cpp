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

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  ll n, k;
  cin >> n >> k;
  ll cmin = n;
  for (ll i = 1; i <= n; i++) {
    if (i*(i-1)/2 >= k) {
      cmin = i;
      break;
    }
  }
  // diff > 0
  ll diff = k - (cmin-1)*(cmin-2)/2;
  int ans[n];
  // no touch
  for (int i = cmin; i < n; i++) {
    ans[i] = i+1;
  }
  // intersect
  int seen = false;
  for (int i = 0; i < cmin; i++) {
    if (i == diff) {
      ans[cmin-1] = cmin-i;
      seen = true;
    }
    else {
      ans[i-seen] = cmin-i;
    }
  }

#ifdef DEBUG
  set<int> st;
  for (int i = 0; i < n; i++) {
    st.insert(ans[i]);
  } assert(st.size() == n);
#endif
  for (int i = 0; i < n; i++) {
    cout << ans[i] << " ";
  } cout << endl;

  return 0;
}
